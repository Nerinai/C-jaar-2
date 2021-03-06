#include "hwlib.hpp"
#include "player.hpp"
void play_melody( player & p ){
	p.play( note{ 621, 93750} );
	p.play( note{ 587, 93750} );
	p.play( note{ 621, 93750} );
	p.play( note{ 739, 375000} );
	p.play( note{ 830, 93750} );
	p.play( note{ 739, 93750} );
	p.play( note{ 698, 93750} );
	p.play( note{ 739, 93750} );
	p.play( note{ 466, 375000} );
	p.play( note{ 494, 187500} );
	p.play( note{ 466, 187500} );
	p.play( note{ 440, 187500} );
	p.play( note{ 466, 187500} );
	p.play( note{ 1396, 187500} );
	p.play( note{ 1242, 187500} );
	p.play( note{ 1174, 187500} );
	p.play( note{ 1242, 187500} );
	p.play( note{ 1396, 187500} );
	p.play( note{ 1242, 187500} );
	p.play( note{ 1174, 187500} );
	p.play( note{ 1242, 187500} );
	p.play( note{ 1478, 375000} );
	p.play( note{ 1242, 375000} );
	p.play( note{ 1478, 375000} );
	p.play( note{ 1108, 93750} );
	p.play( note{ 1242, 93750} );
	p.play( note{ 1396, 187500} );
	p.play( note{ 1242, 375000} );
	p.play( note{ 1108, 375000} );
	p.play( note{ 1242, 375000} );
	p.play( note{ 1108, 93750} );
	p.play( note{ 1242, 93750} );
	p.play( note{ 1396, 187500} );
	p.play( note{ 1242, 375000} );
	p.play( note{ 1108, 375000} );
	p.play( note{ 1242, 375000} );
	p.play( note{ 1108, 93750} );
	p.play( note{ 1242, 93750} );
	p.play( note{ 1396, 187500} );
	p.play( note{ 1242, 375000} );
	p.play( note{ 1108, 375000} );
	p.play( note{ 1046, 375000} );
	p.play( note{ 466, 750000} );
	p.play( note{ 698, 187500} );
	p.play( note{ 621, 93750} );
	p.play( note{ 587, 187500} );
	p.play( note{ 621, 187500} );
	p.play( note{ 739, 750000} );
	p.play( note{ 830, 187500} );
	p.play( note{ 739, 187500} );
	p.play( note{ 698, 187500} );
	p.play( note{ 739, 187500} );
	p.play( note{ 466, 750000} );
	p.play( note{ 494, 187500} );
	p.play( note{ 466, 187500} );
	p.play( note{ 440, 187500} );
	p.play( note{ 466, 187500} );
	p.play( note{ 1396, 187500} );
	p.play( note{ 1242, 187500} );
	p.play( note{ 1174, 187500} );
	p.play( note{ 1242, 187500} );
	p.play( note{ 1396, 187500} );
	p.play( note{ 1242, 187500} );
	p.play( note{ 1174, 187500} );
	p.play( note{ 1242, 187500} );
	p.play( note{ 1478, 750000} );
	p.play( note{ 1242, 375000} );
	p.play( note{ 1478, 375000} );
	p.play( note{ 1108, 93750} );
	p.play( note{ 1242, 93750} );
	p.play( note{ 1396, 187500} );
	p.play( note{ 1242, 375000} );
	p.play( note{ 1108, 375000} );
	p.play( note{ 1242, 375000} );
	p.play( note{ 1108, 93750} );
	p.play( note{ 1242, 93750} );
	p.play( note{ 1396, 187500} );
	p.play( note{ 1242, 375000} );
	p.play( note{ 1108, 375000} );
	p.play( note{ 1242, 375000} );
	p.play( note{ 1108, 93750} );
	p.play( note{ 1242, 93750} );
	p.play( note{ 1396, 187500} );
	p.play( note{ 1242, 375000} );
	p.play( note{ 1108, 375000} );
	p.play( note{ 1046, 375000} );
	p.play( note{ 466, 750000} );
	p.play( note{ 466, 375000} );
	p.play( note{ 494, 375000} );
	p.play( note{ 1108, 375000} );
	p.play( note{ 1108, 375000} );
	p.play( note{ 1242, 187500} );
	p.play( note{ 1108, 187500} );
	p.play( note{ 494, 187500} );
}

int main (void) {

	WDT->WDT_MR = WDT_MR_WDDIS;

	namespace target = hwlib::target;

	hwlib::wait_ms( 500 );

	auto lsp = target::pin_out ( target::pins::d7 );
	auto p = lsp_player ( lsp );
	play_melody(p);
}