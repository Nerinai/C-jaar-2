#ifndef PLAYER_HPP
#define PLAYER_HPP

class note {
public:
   const int frequency;
   const int duration;
   
   // from https://www.seventhstring.com/resources/notefrequencies.html
   static const int A4  = 440;
   static const int A4s = 466;
   static const int B4  = 494;
   static const int C5  = 523;
   static const int C5s = 554;
   static const int D5  = 587;
   static const int D5s = 622;
   static const int E5  = 659;
   static const int F5  = 698;
   static const int F5s = 740;
   static const int G5  = 784;
   static const int G5s = 830;
   static const int A5  = 880;
   static const int A5s = 932;
   static const int B5  = 987;
   
   static const int dF = 1'000'000;
   static const int dH = dF / 2;
   static const int dQ = dF / 4;
};

class player {
public:   
   virtual void play( const note & n ) = 0;
};


// ===========================================================================
//
// simple note player for a speaker connected to a GPIO pin
//
// ===========================================================================

class lsp_player : public player {
private:   
   hwlib::pin_out & lsp;
public: 
   lsp_player( hwlib::pin_out & lsp ):
      lsp( lsp )
   {}
   
   void play( const note & n ) override {
      if( n.frequency == 0 ){
         hwlib::wait_us( n.duration );
      } else {
         auto end = hwlib::now_us() + n.duration;
         auto half_period = 1'000'000 / ( 2 * n.frequency );    
         while( end > hwlib::now_us() ){
            lsp.set( 1 );
            hwlib::wait_us( half_period );
            lsp.set( 0 );
            hwlib::wait_us( half_period );
         }
      }     
   }
};

#endif // PLAYER_HPP
