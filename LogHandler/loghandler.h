#ifndef LOGHANDLER_H
#define LOGHANDLER_H

#include <QtGlobal>
#include <QString>
#include <QPointer>
#include <QMap>
#include <QMutex>

class LoggerRelay;

class LogHandler
{
public:
    LogHandler();
    ~LogHandler();

    void setRelay(LoggerRelay *relay);

    void install();
    void uninstall();

    static void staticMessageHandler(QtMsgType type,
                                     const QMessageLogContext &context,
                                     const QString &msg);

    void applyFilterRules(const QString &rules);

    void setCategoryLevels(const QString &category,
                           int enableDebug,
                           int enableInfo,
                           int enableWarning,
                           int enableCritical);

    void clearCategoryLevels();

    void setTimestampFormat(const QString &format);
    void setIncludeContextFileLine(bool enabled);

private:
    void handle(QtMsgType type,
                const QMessageLogContext &context,
                const QString &msg);

    static QString levelToText(QtMsgType type);
    QString categoryFromContext(const QMessageLogContext &context) const;
    QString formatLine(QtMsgType type,
                       const QMessageLogContext &context,
                       const QString &msg) const;

    void rebuildRulesLocked();

private:
    struct CategoryLevels
    {
        int debugEnabled;
        int infoEnabled;
        int warningEnabled;
        int criticalEnabled;

        CategoryLevels()
            : debugEnabled(-1),
            infoEnabled(-1),
            warningEnabled(-1),
            criticalEnabled(-1)
        {
        }
    };

    static LogHandler *s_instance;

    QPointer<LoggerRelay> m_relay;
    bool m_installed;

    QString m_timestampFormat;
    bool m_includeContextFileLine;

    QMap<QString, CategoryLevels> m_categoryLevelsMap;
    QString m_currentRules;
    QMutex m_mutex;

    // NEW: previous handler to forward to (so Creator still gets output)
    QtMessageHandler m_prevHandler;
};

#endif // LOGHANDLER_H
