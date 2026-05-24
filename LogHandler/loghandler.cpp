#include "loghandler.h"
#include "loggerrelay.h"

#include <QDateTime>
#include <QLoggingCategory>
#include <QTextStream>
#include <QMutexLocker>

LogHandler *LogHandler::s_instance = nullptr;

LogHandler::LogHandler()
    : m_relay(nullptr),
    m_installed(false),
    m_timestampFormat(QStringLiteral("dd/MM/yyyy hh:mm:ss")),
    m_includeContextFileLine(false),
    m_prevHandler(nullptr) // initialize
{
}

LogHandler::~LogHandler()
{
    if (m_installed)
    {
        uninstall();
    }
}

void LogHandler::setRelay(LoggerRelay *relay)
{
    m_relay = relay;
}

void LogHandler::install()
{
    s_instance = this;

    // Save previous handler and install ours
    m_prevHandler = qInstallMessageHandler(&LogHandler::staticMessageHandler);
    m_installed = true;
}

void LogHandler::uninstall()
{
    // Restore previous handler
    qInstallMessageHandler(m_prevHandler);
    m_prevHandler = nullptr;

    m_installed = false;

    if (s_instance == this)
    {
        s_instance = nullptr;
    }
}

void LogHandler::applyFilterRules(const QString &rules)
{
    QMutexLocker locker(&m_mutex);
    m_currentRules = rules;
    QLoggingCategory::setFilterRules(m_currentRules);
}

void LogHandler::setCategoryLevels(const QString &category,
                                   int enableDebug,
                                   int enableInfo,
                                   int enableWarning,
                                   int enableCritical)
{
    QMutexLocker locker(&m_mutex);

    if (!m_categoryLevelsMap.contains(category))
    {
        CategoryLevels levels;
        m_categoryLevelsMap.insert(category, levels);
    }

    CategoryLevels levels = m_categoryLevelsMap.value(category);

    if (enableDebug >= -1 && enableDebug <= 1)
    {
        levels.debugEnabled = enableDebug;
    }
    if (enableInfo >= -1 && enableInfo <= 1)
    {
        levels.infoEnabled = enableInfo;
    }
    if (enableWarning >= -1 && enableWarning <= 1)
    {
        levels.warningEnabled = enableWarning;
    }
    if (enableCritical >= -1 && enableCritical <= 1)
    {
        levels.criticalEnabled = enableCritical;
    }

    m_categoryLevelsMap[category] = levels;

    rebuildRulesLocked();
}

void LogHandler::clearCategoryLevels()
{
    QMutexLocker locker(&m_mutex);
    m_categoryLevelsMap.clear();
    m_currentRules.clear();
    QLoggingCategory::setFilterRules(QString());
}

void LogHandler::setTimestampFormat(const QString &format)
{
    m_timestampFormat = format;
}

void LogHandler::setIncludeContextFileLine(bool enabled)
{
    m_includeContextFileLine = enabled;
}

void LogHandler::staticMessageHandler(QtMsgType type,
                                      const QMessageLogContext &context,
                                      const QString &msg)
{
    if (s_instance != nullptr)
    {
        s_instance->handle(type, context, msg);
    }
    else
    {
        // No instance to handle; do nothing here. Creator will miss it unless
        // a previous handler exists (but there isn't one installed at this point).
        if (type == QtFatalMsg)
        {
            abort();
        }
    }
}

void LogHandler::handle(QtMsgType type,
                        const QMessageLogContext &context,
                        const QString &msg)
{
    // 1) Emit to UI via LoggerRelay
    const QString line = formatLine(type, context, msg);

    if (!m_relay.isNull())
    {
        // Queued connection is used on the receiver side
        emit m_relay->message(line);
    }

    // 2) Forward to previous handler so Qt Creator still receives messages
    if (m_prevHandler != nullptr)
    {
        m_prevHandler(type, context, msg);
    }

    // 3) Preserve fatal semantics (default handler also aborts,
    //    but in case previous handler was null, ensure abort here)
    if (type == QtFatalMsg)
    {
        abort();
    }
}

QString LogHandler::levelToText(QtMsgType type)
{
    if (type == QtDebugMsg)
    {
        return QString("{Debug}\t\t");
    }
#if (QT_VERSION >= QT_VERSION_CHECK(5, 5, 0))
    if (type == QtInfoMsg)
    {
        return QString("{Info}\t\t");
    }
#endif
    if (type == QtWarningMsg)
    {
        return QString("{Warning}\t");
    }
    if (type == QtCriticalMsg)
    {
        return QString("{Critical}\t");
    }
    if (type == QtFatalMsg)
    {
        return QString("{Fatal}\t\t");
    }

    return QString("{Unknown}\t");
}

QString LogHandler::categoryFromContext(const QMessageLogContext &context) const
{
    const char *cat = context.category;
    if (cat == nullptr || cat[0] == '\0')
    {
        return QStringLiteral("default");
    }
    return QString::fromLatin1(cat);
}

QString LogHandler::formatLine(QtMsgType type,
                               const QMessageLogContext &context,
                               const QString &msg) const
{
    const QString dt = QDateTime::currentDateTime().toString(m_timestampFormat);
    const QString category = categoryFromContext(context);

    if (m_includeContextFileLine)
    {
        const char *file = context.file != nullptr ? context.file : "";
        int lineNo = context.line;
        return QString("[%1] [%2] %3%4 (%5:%6)")
            .arg(dt)
            .arg(category)
            .arg(LogHandler::levelToText(type))
            .arg(msg)
            .arg(QString::fromLatin1(file))
            .arg(lineNo);
    }

    return QString("[%1] [%2] %3%4")
        .arg(dt)
        .arg(category)
        .arg(LogHandler::levelToText(type))
        .arg(msg);
}

void LogHandler::rebuildRulesLocked()
{
    QString rulesText;
    QTextStream stream(&rulesText);

    QMap<QString, CategoryLevels>::const_iterator it = m_categoryLevelsMap.constBegin();
    while (it != m_categoryLevelsMap.constEnd())
    {
        const QString category = it.key();
        const CategoryLevels levels = it.value();

        if (levels.debugEnabled != -1)
        {
            stream << category << ".debug=" << (levels.debugEnabled == 1 ? "true" : "false") << '\n';
        }
#if (QT_VERSION >= QT_VERSION_CHECK(5, 5, 0))
        if (levels.infoEnabled != -1)
        {
            stream << category << ".info=" << (levels.infoEnabled == 1 ? "true" : "false") << '\n';
        }
#endif
        if (levels.warningEnabled != -1)
        {
            stream << category << ".warning=" << (levels.warningEnabled == 1 ? "true" : "false") << '\n';
        }
        if (levels.criticalEnabled != -1)
        {
            stream << category << ".critical=" << (levels.criticalEnabled == 1 ? "true" : "false") << '\n';
        }

        ++it;
    }

    m_currentRules = rulesText;
    QLoggingCategory::setFilterRules(m_currentRules);
}
