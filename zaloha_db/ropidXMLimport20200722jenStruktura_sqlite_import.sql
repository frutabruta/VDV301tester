
-- phpMyAdmin SQL Dump
-- version 4.6.6deb5
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Jul 22, 2020 at 06:45 PM
-- Server version: 10.0.28-MariaDB-2+b1
-- PHP Version: 7.3.19-1~deb10u1

/*SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO"; */
/*SET time_zone = "+00:00";*/


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `ropidXMLimport`
--

-- --------------------------------------------------------

--
-- Table structure for table `ch`
--

CREATE TABLE `ch` (
  `c` int(11) NOT NULL,
  `n` varchar(100) /*COLLATE utf8_czech_ci */NOT NULL
) /*ENGINE=InnoDB*/ DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci COMMENT='charakter výkonu';

-- --------------------------------------------------------

--
-- Table structure for table `d`
--

CREATE TABLE `d` (
  `c` int(11) NOT NULL,
  `n` varchar(100) COLLATE utf8_czech_ci NOT NULL,
  `kj` tinyint(4) NOT NULL,
  `ncis` varchar(100) COLLATE utf8_czech_ci NOT NULL,
  `ico` int(11) NOT NULL,
  `dic` varchar(30) COLLATE utf8_czech_ci NOT NULL,
  `ul` varchar(100) COLLATE utf8_czech_ci NOT NULL,
  `me` varchar(100) COLLATE utf8_czech_ci NOT NULL,
  `psc` int(11) NOT NULL,
  `tel` varchar(50) COLLATE utf8_czech_ci NOT NULL,
  `em` varchar(100) COLLATE utf8_czech_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

-- --------------------------------------------------------

--
-- Table structure for table `dd`
--

CREATE TABLE `dd` (
  `c` int(11) NOT NULL,
  `z` varchar(10) COLLATE utf8_czech_ci NOT NULL,
  `n` varchar(50) COLLATE utf8_czech_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

-- --------------------------------------------------------

--
-- Table structure for table `ids`
--

CREATE TABLE `ids` (
  `c` int(11) NOT NULL,
  `z` varchar(10) COLLATE utf8_czech_ci NOT NULL,
  `n` varchar(100) COLLATE utf8_czech_ci NOT NULL,
  `tapoj` varchar(100) COLLATE utf8_czech_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

-- --------------------------------------------------------

--
-- Table structure for table `l`
--

CREATE TABLE `l` (
  `c` int(11) NOT NULL,
  `d` int(11) NOT NULL,
  `kj` tinyint(4) NOT NULL DEFAULT '0',
  `lc` int(7) NOT NULL,
  `a` varchar(20) COLLATE utf8_czech_ci DEFAULT NULL,
  `aois` varchar(20) COLLATE utf8_czech_ci DEFAULT NULL,
  `tl` varchar(20) COLLATE utf8_czech_ci DEFAULT NULL,
  `n` varchar(100) COLLATE utf8_czech_ci DEFAULT NULL,
  `kup` int(11) DEFAULT NULL COMMENT 'číslo kategorie preference',
  `ids` tinyint(1) DEFAULT '1',
  `noc` tinyint(1) DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

-- --------------------------------------------------------

--
-- Table structure for table `m`
--

CREATE TABLE `m` (
  `c` int(11) NOT NULL COMMENT 'číslo majitele označníku',
  `n` varchar(200) COLLATE utf8_czech_ci NOT NULL COMMENT 'název',
  `z` varchar(10) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'zkratka',
  `t` varchar(20) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'telefon',
  `e` varchar(100) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'e-mail'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci COMMENT='majitelé označníků';

-- --------------------------------------------------------

--
-- Table structure for table `o`
--

CREATE TABLE `o` (
  `l` int(11) NOT NULL COMMENT 'číslo kmenové linky',
  `p` int(11) NOT NULL COMMENT 'číslo kmenového pořadí',
  `kj` varchar(50) COLLATE utf8_czech_ci NOT NULL COMMENT 'kalendář jízd',
  `prej` varchar(500) COLLATE utf8_czech_ci NOT NULL COMMENT 'čísla přejezdových linek, odděleno čárkami',
  `sp` varchar(500) COLLATE utf8_czech_ci NOT NULL COMMENT 'pole id spojů jak jdou za sebou na dráze vozu',
  `id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci COMMENT='oběhy';

-- --------------------------------------------------------

--
-- Table structure for table `p`
--

CREATE TABLE `p` (
  `c` int(11) NOT NULL,
  `kj` tinyint(4) NOT NULL DEFAULT '0',
  `z` varchar(10) COLLATE utf8_czech_ci NOT NULL COMMENT 'zkratka názvu provozovny',
  `n` varchar(100) COLLATE utf8_czech_ci NOT NULL,
  `d` int(11) NOT NULL,
  `dd` int(11) NOT NULL,
  `u` int(11) DEFAULT NULL,
  `telz` varchar(50) COLLATE utf8_czech_ci DEFAULT NULL,
  `mail` varchar(100) COLLATE utf8_czech_ci DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

-- --------------------------------------------------------

--
-- Table structure for table `po`
--

CREATE TABLE `po` (
  `c` int(11) NOT NULL,
  `t` varchar(300) COLLATE utf8_czech_ci NOT NULL,
  `zkr1` varchar(300) COLLATE utf8_czech_ci NOT NULL,
  `zkr2` varchar(300) COLLATE utf8_czech_ci NOT NULL,
  `ois` tinyint(1) NOT NULL DEFAULT '0',
  `n` tinyint(1) NOT NULL DEFAULT '0',
  `tn` varchar(10) COLLATE utf8_czech_ci DEFAULT NULL,
  `nl` int(11) DEFAULT NULL,
  `anl` varchar(10) COLLATE utf8_czech_ci DEFAULT NULL,
  `dd` int(11) DEFAULT NULL,
  `cd` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

-- --------------------------------------------------------

--
-- Table structure for table `priznaky`
--

CREATE TABLE `priznaky` (
  `id` int(11) NOT NULL,
  `zkratka` varchar(50) COLLATE utf8_czech_ci NOT NULL,
  `popis` varchar(200) COLLATE utf8_czech_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

-- --------------------------------------------------------

--
-- Table structure for table `r`
--

CREATE TABLE `r` (
  `c` int(11) NOT NULL COMMENT 'číslo kategorie úrovně preference',
  `pop` varchar(100) COLLATE utf8_czech_ci NOT NULL COMMENT 'název kategorie úrovně preference'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci COMMENT='preference';

-- --------------------------------------------------------

--
-- Table structure for table `s`
--

CREATE TABLE `s` (
  `s` int(11) NOT NULL COMMENT 'ID spoje v rámci dávky',
  `id` int(11) NOT NULL COMMENT 'ID grafikonu v ASW jř',
  `l` int(11) NOT NULL COMMENT 'číslo linky spoje (integer kvůli CISovým linkám)',
  `p` int(11) NOT NULL COMMENT 'číslo pořadí, do kterého je spoj zařazen',
  `sm` tinyint(1) NOT NULL DEFAULT '1' COMMENT 'směr spoje, výchozí je true= tam',
  `dd` int(11) NOT NULL COMMENT 'číslo druhu dopravy',
  `pr` int(11) NOT NULL COMMENT 'číslo provozovny spoje',
  `d` int(11) DEFAULT NULL COMMENT '(useless)číslo dopravce spoje',
  `tv` int(11) NOT NULL COMMENT 'číslo typu vozu spoje',
  `kj` varchar(50) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'kalendář jízd, bitová maska od DatumOd do DatumDo',
  `ty` varchar(10) COLLATE utf8_czech_ci NOT NULL COMMENT 'číslo typu výkonu spoje',
  `ch` tinyint(4) NOT NULL COMMENT 'číslo charakteru výkonu spoje',
  `po` int(11) NOT NULL COMMENT 'poznámky spoje (list)',
  `np` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'příznak nízkopodlažní',
  `ids` tinyint(1) NOT NULL DEFAULT '1' COMMENT 'příznak zařazení spoje do IDS (dle charakteru výkonu)',
  `jk` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'Pří.: jízdní kola',
  `vy` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'Pří.: výlukový',
  `sp1` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'Pří.: první spoj',
  `spN` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'Pří.: poslední spoj',
  `doh` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'Pří.: dohodnutý',
  `pos` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'příznak posilový spoj',
  `man` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'příznak manipulační jízda',
  `neve` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'příznak neveřejný spoj',
  `c` smallint(6) NOT NULL COMMENT 'explicitně zadané číslo spoje ROPID',
  `ns` int(11) DEFAULT NULL COMMENT 'ID následujícího spoje',
  `x` int(11) NOT NULL COMMENT 'pole všech zastavení spoje (XML) element',
  `o_id` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

-- --------------------------------------------------------

--
-- Table structure for table `sp_po`
--

CREATE TABLE `sp_po` (
  `id` int(11) NOT NULL,
  `s_id` int(11) NOT NULL,
  `po_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

-- --------------------------------------------------------

--
-- Table structure for table `t`
--

CREATE TABLE `t` (
  `u` int(11) NOT NULL COMMENT 'číslo uzlu',
  `z` int(11) NOT NULL COMMENT 'číslo zastávky',
  `kj` tinyint(1) DEFAULT '0' COMMENT 'kalendář platnosti tabla',
  `ois` int(11) DEFAULT NULL COMMENT 'číslo OIS',
  `cis` int(11) NOT NULL COMMENT 'číslo CIS',
  `nza` varchar(100) COLLATE utf8_czech_ci NOT NULL COMMENT 'název zastávky',
  `ri` varchar(25) COLLATE utf8_czech_ci NOT NULL COMMENT 'text pro pal. PC',
  `ji` varchar(25) COLLATE utf8_czech_ci NOT NULL COMMENT 'text pro jízdenku',
  `vtm` varchar(40) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'text pro vnitřní tablo (MHD)',
  `vtn` varchar(40) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'text pro vnitřní tablo',
  `btm` varchar(40) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'text pro boční tablo (MHD)',
  `btn` varchar(40) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'text pro boční tablo',
  `ctm` varchar(40) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'text pro čelní tablo (MHD)',
  `ctn` varchar(40) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'text pro čelní tablo',
  `ztm` varchar(40) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'text pro zadní tablo (MHD)',
  `ztn` varchar(40) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'text pro zadní tablo',
  `lcdm` varchar(40) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'text pro LCD (MHD)',
  `lcdn` varchar(40) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'text pro LCD',
  `hl` varchar(400) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'text doplňkového hlášení',
  `n` varchar(200) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'plný název zastávky',
  `nf` varchar(200) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'plný název zastávky foneticky'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

-- --------------------------------------------------------

--
-- Table structure for table `tv`
--

CREATE TABLE `tv` (
  `c` int(11) NOT NULL,
  `z` varchar(10) COLLATE utf8_czech_ci NOT NULL,
  `n` varchar(1000) COLLATE utf8_czech_ci NOT NULL,
  `dd` int(11) NOT NULL,
  `np` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

-- --------------------------------------------------------

--
-- Table structure for table `ty`
--

CREATE TABLE `ty` (
  `c` int(11) NOT NULL COMMENT 'číslo typ výkonu',
  `n` varchar(50) COLLATE utf8_czech_ci NOT NULL COMMENT 'název typu výkonu',
  `li` tinyint(1) NOT NULL DEFAULT '1' COMMENT 'přiznak, zda je linkový'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci COMMENT='typ výkonu';

-- --------------------------------------------------------

--
-- Table structure for table `x`
--

CREATE TABLE `x` (
  `u` int(11) NOT NULL,
  `z` int(11) NOT NULL,
  `p` int(11) DEFAULT NULL,
  `o` int(11) DEFAULT NULL,
  `t` varchar(30) COLLATE utf8_czech_ci NOT NULL,
  `ty` tinyint(4) NOT NULL,
  `ces` tinyint(1) DEFAULT '1',
  `po` int(11) DEFAULT NULL,
  `zn` tinyint(1) NOT NULL DEFAULT '0',
  `na` tinyint(1) NOT NULL DEFAULT '0',
  `vyst` tinyint(1) NOT NULL DEFAULT '0',
  `nast` tinyint(1) NOT NULL DEFAULT '0',
  `poj` tinyint(1) NOT NULL DEFAULT '0',
  `bp` tinyint(1) NOT NULL DEFAULT '0',
  `s` tinyint(1) NOT NULL DEFAULT '0',
  `s1` tinyint(1) NOT NULL DEFAULT '0',
  `s2` tinyint(1) NOT NULL,
  `zsol` tinyint(1) NOT NULL,
  `icls` int(11) NOT NULL,
  `xA` tinyint(1) NOT NULL,
  `xB` tinyint(1) NOT NULL,
  `xC` tinyint(1) NOT NULL,
  `xD` tinyint(1) NOT NULL,
  `xVla` tinyint(1) NOT NULL,
  `xLod` tinyint(1) NOT NULL,
  `xLet` tinyint(1) NOT NULL,
  `id` int(11) NOT NULL,
  `s_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

-- --------------------------------------------------------

--
-- Table structure for table `z`
--

CREATE TABLE `z` (
  `id` int(11) NOT NULL COMMENT 'vlastní id',
  `u` int(11) NOT NULL COMMENT 'číslo uzlu',
  `z` int(11) NOT NULL COMMENT 'číslo označníku',
  `kj` varchar(50) COLLATE utf8_czech_ci NOT NULL COMMENT 'kalendář platnosti záznamu zastávky',
  `n` varchar(100) COLLATE utf8_czech_ci NOT NULL COMMENT 'název zastávky (max 50 znaků)',
  `pop` varchar(300) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'popis/směr zastávky pro bližší určení',
  `tu` varchar(50) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'typ uzlu',
  `cis` int(11) NOT NULL DEFAULT '0' COMMENT 'cis číslo zastávky',
  `ois` int(11) DEFAULT NULL COMMENT 'číslo ois (4 znaky)',
  `co` int(11) DEFAULT NULL COMMENT 'číslo obce',
  `no` varchar(100) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'název obce',
  `nco` varchar(100) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'název části obce',
  `spz` varchar(50) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'označení okresu',
  `ids` int(11) DEFAULT NULL COMMENT 'náležitosti ids, cizí klíč',
  `tp` varchar(50) COLLATE utf8_czech_ci NOT NULL COMMENT 'čísla tarifních pásem oddělená čárkou',
  `sx` varchar(100) COLLATE utf8_czech_ci NOT NULL COMMENT 'souřadnice X zastávky (S-JTSK)',
  `sy` varchar(100) COLLATE utf8_czech_ci NOT NULL COMMENT 'souřadnice Y zastávky (S-JTSK)',
  `lat` varchar(100) COLLATE utf8_czech_ci NOT NULL COMMENT 'souřadnice WGS - šířka',
  `lng` varchar(100) COLLATE utf8_czech_ci NOT NULL COMMENT 'souřadnice WGS - délka',
  `sta` varchar(5) COLLATE utf8_czech_ci NOT NULL COMMENT 'označení stanoviště (CIS,MPVnet)',
  `m` int(11) DEFAULT NULL COMMENT 'majitel označníku',
  `ve` tinyint(1) NOT NULL DEFAULT '1' COMMENT 'příznak veřejná/neveřejná',
  `xA` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'přestup Metro A',
  `xB` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'přestup Metro B',
  `xC` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'přestup Metro C',
  `xD` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'přestup Metro D',
  `xVla` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'přestup na vlak',
  `xLod` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'přestup přívoz',
  `xLet` tinyint(1) NOT NULL COMMENT 'přestup na letadlo',
  `kidos` int(11) NOT NULL DEFAULT '301003' COMMENT 'kategorie objektů pro idos (600003 vlak, ostatní 301003)',
  `st` varchar(50) COLLATE utf8_czech_ci DEFAULT NULL COMMENT 'stát',
  `bbn` tinyint(1) NOT NULL COMMENT 'bezbariérová zastávka'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `ch`
--
ALTER TABLE `ch`
  ADD PRIMARY KEY (`c`);

--
-- Indexes for table `d`
--
ALTER TABLE `d`
  ADD PRIMARY KEY (`c`);

--
-- Indexes for table `dd`
--
ALTER TABLE `dd`
  ADD PRIMARY KEY (`c`);

--
-- Indexes for table `ids`
--
ALTER TABLE `ids`
  ADD PRIMARY KEY (`c`);

--
-- Indexes for table `l`
--
ALTER TABLE `l`
  ADD PRIMARY KEY (`c`),
  ADD KEY `d` (`d`),
  ADD KEY `d_2` (`d`);

--
-- Indexes for table `m`
--
ALTER TABLE `m`
  ADD PRIMARY KEY (`c`);

--
-- Indexes for table `o`
--
ALTER TABLE `o`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `p`
--
ALTER TABLE `p`
  ADD PRIMARY KEY (`c`),
  ADD KEY `druhdop` (`dd`),
  ADD KEY `sergsrthxdh` (`d`);

--
-- Indexes for table `po`
--
ALTER TABLE `po`
  ADD PRIMARY KEY (`c`),
  ADD KEY `x_dd` (`dd`);

--
-- Indexes for table `priznaky`
--
ALTER TABLE `priznaky`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `r`
--
ALTER TABLE `r`
  ADD PRIMARY KEY (`c`);

--
-- Indexes for table `s`
--
ALTER TABLE `s`
  ADD PRIMARY KEY (`s`),
  ADD KEY `s_l` (`l`),
  ADD KEY `s_pr` (`pr`),
  ADD KEY `s_tv` (`tv`),
  ADD KEY `s_dd` (`dd`),
  ADD KEY `s_d` (`d`),
  ADD KEY `s_o_id` (`o_id`);

--
-- Indexes for table `sp_po`
--
ALTER TABLE `sp_po`
  ADD PRIMARY KEY (`id`),
  ADD KEY `sppo_sid` (`s_id`),
  ADD KEY `sppo_poid` (`po_id`);

--
-- Indexes for table `t`
--
ALTER TABLE `t`
  ADD PRIMARY KEY (`u`,`z`),
  ADD KEY `t_index` (`z`,`u`);

--
-- Indexes for table `tv`
--
ALTER TABLE `tv`
  ADD PRIMARY KEY (`c`),
  ADD KEY `druhDoptv` (`dd`);

--
-- Indexes for table `ty`
--
ALTER TABLE `ty`
  ADD PRIMARY KEY (`c`);

--
-- Indexes for table `x`
--
ALTER TABLE `x`
  ADD PRIMARY KEY (`id`),
  ADD KEY `tzurtzuru` (`u`),
  ADD KEY `vazbaL` (`z`,`u`),
  ADD KEY `x_sid` (`s_id`);

--
-- Indexes for table `z`
--
ALTER TABLE `z`
  ADD PRIMARY KEY (`id`),
  ADD KEY `kombinace` (`z`,`u`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `dd`
--
ALTER TABLE `dd`
  MODIFY `c` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
--
-- AUTO_INCREMENT for table `o`
--
ALTER TABLE `o`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `priznaky`
--
ALTER TABLE `priznaky`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
--
-- AUTO_INCREMENT for table `x`
--
ALTER TABLE `x`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=82218;
--
-- AUTO_INCREMENT for table `z`
--
ALTER TABLE `z`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'vlastní id', AUTO_INCREMENT=12772;
--
-- Constraints for dumped tables
--

--
-- Constraints for table `l`
--
ALTER TABLE `l`
  ADD CONSTRAINT `l_d` FOREIGN KEY (`d`) REFERENCES `d` (`c`);

--
-- Constraints for table `p`
--
ALTER TABLE `p`
  ADD CONSTRAINT `druhdop` FOREIGN KEY (`dd`) REFERENCES `dd` (`c`),
  ADD CONSTRAINT `sergsrthxdh` FOREIGN KEY (`d`) REFERENCES `d` (`c`);

--
-- Constraints for table `po`
--
ALTER TABLE `po`
  ADD CONSTRAINT `x_dd` FOREIGN KEY (`dd`) REFERENCES `dd` (`c`);

--
-- Constraints for table `s`
--
ALTER TABLE `s`
  ADD CONSTRAINT `s_d` FOREIGN KEY (`d`) REFERENCES `d` (`c`),
  ADD CONSTRAINT `s_dd` FOREIGN KEY (`dd`) REFERENCES `dd` (`c`),
  ADD CONSTRAINT `s_l` FOREIGN KEY (`l`) REFERENCES `l` (`c`),
  ADD CONSTRAINT `s_o_id` FOREIGN KEY (`o_id`) REFERENCES `o` (`id`),
  ADD CONSTRAINT `s_pr` FOREIGN KEY (`pr`) REFERENCES `p` (`c`),
  ADD CONSTRAINT `s_tv` FOREIGN KEY (`tv`) REFERENCES `tv` (`c`);

--
-- Constraints for table `sp_po`
--
ALTER TABLE `sp_po`
  ADD CONSTRAINT `sppo_poid` FOREIGN KEY (`po_id`) REFERENCES `po` (`c`),
  ADD CONSTRAINT `sppo_sid` FOREIGN KEY (`s_id`) REFERENCES `s` (`s`);

--
-- Constraints for table `t`
--
ALTER TABLE `t`
  ADD CONSTRAINT `t_index` FOREIGN KEY (`z`,`u`) REFERENCES `z` (`z`, `u`);

--
-- Constraints for table `tv`
--
ALTER TABLE `tv`
  ADD CONSTRAINT `druhDoptv` FOREIGN KEY (`dd`) REFERENCES `dd` (`c`);

--
-- Constraints for table `x`
--
ALTER TABLE `x`
  ADD CONSTRAINT `vazbaL` FOREIGN KEY (`z`,`u`) REFERENCES `z` (`z`, `u`),
  ADD CONSTRAINT `x_sid` FOREIGN KEY (`s_id`) REFERENCES `s` (`s`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
