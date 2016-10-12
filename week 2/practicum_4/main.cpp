#include "hwlib.hpp"
#include <algorithm>

namespace target = hwlib::target;

namespace hwlib {
   class pin_fixed {
   public:    
      pin_fixed( pin_out & pin, bool v ){
         pin.set( v );
      } 
   };
};

   // The OLED display is connected in a very funny way:
   // the I2C pins are reversed, and two GPIO pins are
   // (mis-) used as ground and power for the display.
   // This works, and makes it very easy to connect the LCD,
   // but don't take this as an advice to connect peripherals is this way
   // unless you know very well what you are doing.
class oled_buffered_d18_d21 {
   target::pin_oc scl, sda;
   hwlib::i2c_bus_bit_banged_scl_sda i2c_bus;
   target::pin_out pin_gnd, pin_vcc;
   hwlib::pin_fixed pin_gnd_fixed, pin_vcc_fixed;
   
public:
   hwlib::glcd_oled_buffered oled;

   oled_buffered_d18_d21():
      scl( target::pins::sda ),
      sda( target::pins::scl ),
      i2c_bus( scl, sda ),
      pin_gnd( target::pins::d19 ),
      pin_vcc( target::pins::d18 ),
      pin_gnd_fixed( pin_gnd, 0 ),
      pin_vcc_fixed( pin_vcc, 1 ),
      oled( i2c_bus, 0x3c )
   {}   
};

namespace hwlib {
   constexpr location operator/( const location & lhs, int rhs ){
      return location( lhs.x / rhs, lhs.y / rhs );
   }

}

constexpr hwlib::location square( const hwlib::location & lhs ){
   auto m = std::min( lhs.x, lhs.y );
   return hwlib::location( m, m );
}

constexpr double pow( double g, int n ){
   double result = 1;
   while( n > 0 ){
       result *= g;
       --n;
   }
   return result;
}

void line(int x0, int y0, int x1, int y1, hwlib::glcd_oled_buffered &w) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    for (;;) {
        w.write({x0, y0}, w.foreground);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = err;
        if (e2 > -dx) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dy) {
            err += dx;
            y0 += sy;
        }
    }
}

constexpr double fac( int n ){
   double result = 1;
   while( n > 0 ){
       result *= n;
       --n;
   }
   return result;
}

constexpr double sin( double a ){
   return 
      a 
      - pow( a, 3 ) / fac( 3 ) 
      + pow( a, 5 ) / fac( 5 ) 
      - pow( a, 7 ) / fac( 7 )
      + pow( a, 9 ) / fac( 9 ) 
      - pow( a, 11 ) / fac( 11 ) 
      + pow( a, 13 ) / fac( 13 )
	  - pow( a, 15 ) / fac( 15 ) 
      + pow( a, 17 ) / fac( 17 ) 
      - pow( a, 19 ) / fac( 19 )
      + pow( a, 21 ) / fac( 21 ) 
      - pow( a, 23 ) / fac( 23 ) 
      + pow( a, 25 ) / fac( 25 );
}

constexpr double cos (double a){
	return
		1 
		- pow(a, 2) / fac(2)
		+ pow(a, 4) / fac(4)
		- pow(a, 6) / fac(6)
		+ pow(a, 8) / fac(8)
		- pow(a, 10) / fac(10)
		+ pow(a, 12) / fac(12)
		- pow(a, 14) / fac(14)
		+ pow(a, 16) / fac(16)
		- pow(a, 18) / fac(18)
		+ pow(a, 20) / fac(20)
		- pow(a, 22) / fac(22)
		+ pow(a, 24) / fac(24);
}

constexpr double radians_from_degrees( int degrees ){
   return 2 * 3.14 * ( degrees / 360.0 );
}

template<int scale>
class lookup_table {
public:
	static const int8_t sinvalues[450];
	
	static constexpr int sinus(int angle){
		return scale * sin(radians_from_degrees(angle));
	}	
	
	static constexpr int sinusget(int angle){
		
		return sinvalues[angle];
	}
	
	static constexpr int cosinget(int angle){
		return sinusget(angle + 90);
	}
	
	lookup_table() = delete;
};

template <int scale>
constexpr int8_t lookup_table<scale>::sinvalues[] = {sinus(0),sinus(1),sinus(2),sinus(3),sinus(4),sinus(5),sinus(6),sinus(7),sinus(8),sinus(9),sinus(10),sinus(11),sinus(12),sinus(13),sinus(14),sinus(15),sinus(16),sinus(17),sinus(18),sinus(19),sinus(20),sinus(21),sinus(22),sinus(23),sinus(24),sinus(25),sinus(26),sinus(27),sinus(28),sinus(29),sinus(30),sinus(31),sinus(32),sinus(33),sinus(34),sinus(35),sinus(36),sinus(37),sinus(38),sinus(39),sinus(40),sinus(41),sinus(42),sinus(43),sinus(44),sinus(45),sinus(46),sinus(47),sinus(48),sinus(49),sinus(50),sinus(51),sinus(52),sinus(53),sinus(54),sinus(55),sinus(56),sinus(57),sinus(58),sinus(59),sinus(60),sinus(61),sinus(62),sinus(63),sinus(64),sinus(65),sinus(66),sinus(67),sinus(68),sinus(69),sinus(70),sinus(71),sinus(72),sinus(73),sinus(74),sinus(75),sinus(76),sinus(77),sinus(78),sinus(79),sinus(80),sinus(81),sinus(82),sinus(83),sinus(84),sinus(85),sinus(86),sinus(87),sinus(88),sinus(89),sinus(90),sinus(91),sinus(92),sinus(93),sinus(94),sinus(95),sinus(96),sinus(97),sinus(98),sinus(99),sinus(100),sinus(101),sinus(102),sinus(103),sinus(104),sinus(105),sinus(106),sinus(107),sinus(108),sinus(109),sinus(110),sinus(111),sinus(112),sinus(113),sinus(114),sinus(115),sinus(116),sinus(117),sinus(118),sinus(119),sinus(120),sinus(121),sinus(122),sinus(123),sinus(124),sinus(125),sinus(126),sinus(127),sinus(128),sinus(129),sinus(130),sinus(131),sinus(132),sinus(133),sinus(134),sinus(135),sinus(136),sinus(137),sinus(138),sinus(139),sinus(140),sinus(141),sinus(142),sinus(143),sinus(144),sinus(145),sinus(146),sinus(147),sinus(148),sinus(149),sinus(150),sinus(151),sinus(152),sinus(153),sinus(154),sinus(155),sinus(156),sinus(157),sinus(158),sinus(159),sinus(160),sinus(161),sinus(162),sinus(163),sinus(164),sinus(165),sinus(166),sinus(167),sinus(168),sinus(169),sinus(170),sinus(171),sinus(172),sinus(173),sinus(174),sinus(175),sinus(176),sinus(177),sinus(178),sinus(179),sinus(180),sinus(181),sinus(182),sinus(183),sinus(184),sinus(185),sinus(186),sinus(187),sinus(188),sinus(189),sinus(190),sinus(191),sinus(192),sinus(193),sinus(194),sinus(195),sinus(196),sinus(197),sinus(198),sinus(199),sinus(200),sinus(201),sinus(202),sinus(203),sinus(204),sinus(205),sinus(206),sinus(207),sinus(208),sinus(209),sinus(210),sinus(211),sinus(212),sinus(213),sinus(214),sinus(215),sinus(216),sinus(217),sinus(218),sinus(219),sinus(220),sinus(221),sinus(222),sinus(223),sinus(224),sinus(225),sinus(226),sinus(227),sinus(228),sinus(229),sinus(230),sinus(231),sinus(232),sinus(233),sinus(234),sinus(235),sinus(236),sinus(237),sinus(238),sinus(239),sinus(240),sinus(241),sinus(242),sinus(243),sinus(244),sinus(245),sinus(246),sinus(247),sinus(248),sinus(249),sinus(250),sinus(251),sinus(252),sinus(253),sinus(254),sinus(255),sinus(256),sinus(257),sinus(258),sinus(259),sinus(260),sinus(261),sinus(262),sinus(263),sinus(264),sinus(265),sinus(266),sinus(267),sinus(268),sinus(269),sinus(270),sinus(271),sinus(272),sinus(273),sinus(274),sinus(275),sinus(276),sinus(277),sinus(278),sinus(279),sinus(280),sinus(281),sinus(282),sinus(283),sinus(284),sinus(285),sinus(286),sinus(287),sinus(288),sinus(289),sinus(290),sinus(291),sinus(292),sinus(293),sinus(294),sinus(295),sinus(296),sinus(297),sinus(298),sinus(299),sinus(300),sinus(301),sinus(302),sinus(303),sinus(304),sinus(305),sinus(306),sinus(307),sinus(308),sinus(309),sinus(310),sinus(311),sinus(312),sinus(313),sinus(314),sinus(315),sinus(316),sinus(317),sinus(318),sinus(319),sinus(320),sinus(321),sinus(322),sinus(323),sinus(324),sinus(325),sinus(326),sinus(327),sinus(328),sinus(329),sinus(330),sinus(331),sinus(332),sinus(333),sinus(334),sinus(335),sinus(336),sinus(337),sinus(338),sinus(339),sinus(340),sinus(341),sinus(342),sinus(343),sinus(344),sinus(345),sinus(346),sinus(347),sinus(348),sinus(349),sinus(350),sinus(351),sinus(352),sinus(353),sinus(354),sinus(355),sinus(356),sinus(357),sinus(358),sinus(359),sinus(360),sinus(361),sinus(362),sinus(363),sinus(364),sinus(365),sinus(366),sinus(367),sinus(368),sinus(369),sinus(370),sinus(371),sinus(372),sinus(373),sinus(374),sinus(375),sinus(376),sinus(377),sinus(378),sinus(379),sinus(380),sinus(381),sinus(382),sinus(383),sinus(384),sinus(385),sinus(386),sinus(387),sinus(388),sinus(389),sinus(390),sinus(391),sinus(392),sinus(393),sinus(394),sinus(395),sinus(396),sinus(397),sinus(398),sinus(399),sinus(400),sinus(401),sinus(402),sinus(403),sinus(404),sinus(405),sinus(406),sinus(407),sinus(408),sinus(409),sinus(410),sinus(411),sinus(412),sinus(413),sinus(414),sinus(415),sinus(416),sinus(417),sinus(418),sinus(419),sinus(420),sinus(421),sinus(422),sinus(423),sinus(424),sinus(425),sinus(426),sinus(427),sinus(428),sinus(429),sinus(430),sinus(431),sinus(432),sinus(433),sinus(434),sinus(435),sinus(436),sinus(437),sinus(438),sinus(439),sinus(440),sinus(441),sinus(442),sinus(443),sinus(444),sinus(445),sinus(446),sinus(447),sinus(448),sinus(449)};

void gwijzer(hwlib::glcd_oled_buffered & oled,int pos){
	line(64, 32, lookup_table<20>::cosinget(pos) + 64, lookup_table<20>::sinusget(pos) + 32, oled);
}

void kwijzer(hwlib::glcd_oled_buffered & oled, int pos){
	line(64, 32, lookup_table<15>::cosinget(pos) + 64, lookup_table<15>::sinusget(pos) + 32, oled);
}

void drawclock(hwlib::glcd_oled_buffered & oled){
	oled.clear();
	for (int i = 0; i < 360; i += 30){
	hwlib::circle(hwlib::location(lookup_table<25>::cosinget(i) + 64,lookup_table<25>::sinusget(i) + 32), 3).draw(oled);
	}
}

void secondending(hwlib::glcd_oled_buffered & oled, int pos){
	hwlib::circle(hwlib::location(lookup_table<30>::cosinget(pos) + 64, lookup_table<30>::sinusget(pos) + 32), 1).draw(oled);
}

void clock(hwlib::glcd_oled_buffered & oled, hwlib::pin_in & uurknop, hwlib::pin_in & minutknop){
	int sec = 270;
	int min = 270;
	int hr = 270;
	
	for (int i = 0; i < 360; i += 30){
	hwlib::circle(hwlib::location(lookup_table<25>::cosinget(i) + 64,lookup_table<25>::sinusget(i) + 32), 3).draw(oled);
	oled.flush();
	}
	
	int tick = 0;
	
	for (;;){
		if (tick == 3){
			sec += 6;
		}
		if ((sec == 270 && tick == 3 )|| !minutknop.get()){
			min += 6;
		}
		if ((min == 270 && sec == 270 && tick == 3) || !uurknop.get()){
			hr += 30;
		}

		if (sec == 360){
			sec = 0;
		} 
		if (min == 360){
			min = 0;
		}
		if ( hr == 360){
			hr = 0;
		}
		
		if (tick < 3){
			tick ++;
		} else {
			tick = 0;
		}
	
	drawclock(oled);
	secondending(oled, sec);
	kwijzer(oled, min);
	gwijzer(oled, hr);
	
	oled.flush();
	hwlib::wait_ms(250);
	}
	
	
	
}

int main( void ){	
   
   // kill the watchdog & wait for the PC console to start
	WDT->WDT_MR = WDT_MR_WDDIS;
	hwlib::wait_ms( 500 );   
   
	auto hw     = oled_buffered_d18_d21();
	auto & oled = hw.oled;
	auto uurpin = target::pin_in  (target::pins::d6);
	auto minutpin = target::pin_in  (target::pins::d7);
	clock(oled, uurpin, minutpin);
return 0;
}