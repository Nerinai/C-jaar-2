#include <iostream>

bool is_digit( char c ){ return ( c >= '0' ) && ( c <= '9' ); }
bool is_lowercase( char c ){ return ( c >= 'a' ) && ( c <= 'z' ); }

int frequencies[] = { 440, 494, 523, 587, 659, 698, 784 };

void decode(const char *s ){
   int def_duration = 4, def_octave = 6, value;
   int duration, octave, frequency;
   int state = 0;
   char def;
   bool dot;
   for( const char * p = s; state >= 0; p++ ){
      const char c = *p;
      switch(state ){
             
         // title 
         case 0:
            if( c == ':' ){
               state = 1;
            } else {
               //hwlib::cout << c;
            } 
            break;
               
          // defaults  
          case 1:
            if( c == ':' ){
               state = 3;
            } if( is_lowercase( c )){
               def = c;
               value = 0;
               state = 2;
            } else {
               //HWLIB_TRACE << "c=[" << c << "]";
            } 
            break;   

         // defaults, letter stored in def
         case 2:
            if( c == '=' ){
               // ignore the =
            } else if( is_digit( c )){
               value = ( 10 * value ) + ( c - '0' );
            } else if(( c == ':' ) || ( c == ',' )) {
               if( def == 'o'){
                  def_octave = value;
               } else if( def == 'd' ){
                  def_duration = value;
               } else if( def == 'b' ){
                  // ignore
               } else {
                  //HWLIB_TRACE << "def=[" << def << "]";
               }   
               state = ( c == ':' ) ? 3 : 1;
            } else {
               //HWLIB_TRACE << "c=[" << c << "]";
            }
            break;
            
         // note start, set defaults
         case 3:  
            duration = def_duration;
            octave = def_octave;
            state = 4;
            dot = 0;
            // fallthrough!!
               
         // duration 1  
         case 4:   
            if( c == '\0' ){
               state = -1;
               break;
            } else if( is_digit( c )){
               duration = c -'0';
               state = 5;
               break;
            }            
            // fallthrough!
            
         // duration 2 
         case 5:   
            if( is_digit( c )){
               duration = ( duration * 10 ) + ( c -'0' );
               state = 6;
               break;
            }            
            // fallthrough!
               
         // note letter   
         case 6:   
            if( is_lowercase( c )){
               if( c == 'p' ){
                   frequency = 0;
               } else {
                  frequency = frequencies[ c - 'a' ]; 
               }   
            } else {
               //HWLIB_TRACE << "c=[" << c << "]";
            }   
            state = 7;
            break;
               
         // optional #   
         case 7:   
            if( c == '#' ){
               frequency = 10595 * frequency / 10000;
               state = 8;
               break;
            }
            // fallthrough!

         // optional .
         case 8:
            if( c == '.' ){
               dot = 1;
               state = 9;
               break;
            }            
            // fallthrough!

         case 9:
            if( is_digit( c )){
               octave = c - '0';
               state = 10;
               break;
            }        
            // fallthrough!
               
         case 10:   
            if( ( c == ',' ) || ( c == '\0') ){
               while( octave > 5 ){ --octave; frequency *= 2; }
               duration = 2000000 / duration;
               if( dot ){
                  duration = 3 * duration / 2;
               }

               std::cout
					<< "	p.play( note{ " << frequency << ", " << duration << "} );\n"; 
               state = 4;
            } else {
               //HWLIB_TRACE << "c=[" << c << "]";
            }
            if( c == '\0' ){
               state = -1;
            }
            break;            
      }         
   }
   //HWLIB_TRACE << "done";
}

int main (int argc, char ** argv){
	int freq = 50;
	int dur = 99;
	std::cout
		<< "#include \"hwlib.hpp\"\n"
		//<< "#include \"melody.hpp\"\n"
		<< "#include \"player.hpp\"\n"
		<< "void " << argv[1] << "( player & p ){\n";
	decode(argv[2]);
	std::cout
		<< "}\n\n"
		<<"int main (void) {\n\n"
		<<"	WDT->WDT_MR = WDT_MR_WDDIS;\n\n"
		<<"	namespace target = hwlib::target;\n\n"
		<<"	hwlib::wait_ms( 500 );\n\n"
		<<"	auto lsp = target::pin_out ( target::pins::d7 );\n"
		<<"	auto p = lsp_player ( lsp );\n"
		<<"	play_melody(p);\n"
		<<"}";
		return 0;
		
}