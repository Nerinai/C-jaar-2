#include "hwlib.hpp"
#include "player.hpp"
void play_melody( player & p ){
	p.play( note{ 1396, 250000} );
	p.play( note{ 0, 125000} );
	p.play( note{ 698, 125000} );
	p.play( note{ 523, 125000} );
	p.play( note{ 0, 125000} );
	p.play( note{ 698, 1000000} );
	p.play( note{ 0, 250000} );
	p.play( note{ 784, 250000} );
	p.play( note{ 440, 8} );
	p.play( note{ 523, 250000} );
	p.play( note{ 698, 8} );
	p.play( note{ 0, 250000} );
	p.play( note{ 440, 125000} );
	p.play( note{ 523, 125000} );
	p.play( note{ 698, 250000} );
	p.play( note{ 523, 250000} );
	p.play( note{ 784, 250000} );
	p.play( note{ 698, 8} );
	p.play( note{ 0, 250000} );
	p.play( note{ 0, 250000} );
	p.play( note{ 587, 250000} );
	p.play( note{ 0, 125000} );
	p.play( note{ 587, 125000} );
	p.play( note{ 523, 125000} );
	p.play( note{ 440, 250000} );
	p.play( note{ 0, 125000} );
	p.play( note{ 523, 16} );
	p.play( note{ 0, 125000} );
}

int main (void) {

	WDT->WDT_MR = WDT_MR_WDDIS;

	namespace target = hwlib::target;

	hwlib::wait_ms( 500 );

	auto lsp = target::pin_out ( target::pins::d7 );
	auto p = lsp_player ( lsp );
	play_melody(p);
}