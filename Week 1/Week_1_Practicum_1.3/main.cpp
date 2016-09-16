#include "hwlib.hpp"
#include "player.hpp"
void play_melody( player & p ){
	p.play( note{ 440, 125000} );
	p.play( note{ 494, 125000} );
	p.play( note{ 523, 1000000} );
	p.play( note{ 494, 1000000} );
	p.play( note{ 440, 250000} );
	p.play( note{ 0, 125000} );
	p.play( note{ 784, 250000} );
	p.play( note{ 0, 125000} );
	p.play( note{ 784, 16} );
	p.play( note{ 0, 250000} );
	p.play( note{ 587, 8} );
	p.play( note{ 784, 1000000} );
	p.play( note{ 698, 250000} );
	p.play( note{ 0, 125000} );
	p.play( note{ 587, 250000} );
	p.play( note{ 659, 1000000} );
	p.play( note{ 0, 2} );
	p.play( note{ 0, 250000} );
	p.play( note{ 440, 125000} );
	p.play( note{ 523, 1000000} );
	p.play( note{ 494, 1000000} );
	p.play( note{ 440, 250000} );
	p.play( note{ 0, 125000} );
	p.play( note{ 784, 250000} );
	p.play( note{ 0, 125000} );
	p.play( note{ 784, 16} );
	p.play( note{ 0, 250000} );
	p.play( note{ 587, 8} );
	p.play( note{ 784, 250000} );
	p.play( note{ 0, 250000} );
	p.play( note{ 784, 250000} );
	p.play( note{ 698, 250000} );
	p.play( note{ 0, 125000} );
	p.play( note{ 659, 250000} );
	p.play( note{ 0, 125000} );
	p.play( note{ 587, 250000} );
	p.play( note{ 659, 1000000} );
}

int main (void) {

	WDT->WDT_MR = WDT_MR_WDDIS;

	namespace target = hwlib::target;

	hwlib::wait_ms( 500 );

	auto lsp = target::pin_out ( target::pins::d7 );
	auto p = lsp_player ( lsp );
	play_melody(p);
}