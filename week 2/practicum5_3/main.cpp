#include <hwlib.hpp>

extern "C" {
	void put_int(int c){
		hwlib::cout << " " << c <<hwlib::endl;
		hwlib::wait_ms(500);
	}

	void put_char( char c ){
      hwlib::cout << c;
	  //hwlib::wait_ms(100);
   }

   void decompress(void);

}

int main(void){
	WDT->WDT_MR = WDT_MR_WDDIS;
	hwlib::wait_ms( 500 );


	//hwlib::cout << "chris zecht dat dit moet" << hwlib::endl;
	decompress();
	//hwlib::cout << "idem" << hwlib::endl;

return 1;
}
