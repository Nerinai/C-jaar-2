
   /*int lenght = 20;
   int angle = 90;*/
   

  /* hwlib::circle( oled.size / 2 , square( oled.size ).x / 2 - 3 ).draw( oled );    
   oled.flush();*/
   	/*int x = lenght * cos(radians_from_degrees(angle)) + origin.x;
	int y = lenght * sin(radians_from_degrees(angle)) + origin.y;
	hwlib::location des (x, y);*/
	 locations;
	
	auto cosin = lookup_table<360, int>(
	[]( int x ) -> int { return 
	); 
	auto sinus = lookup_table<360, int>
	
	for (int i = 0; i < 360; i++){
		oled.clear();
		hwlib::circle(hwlib::location(cosin[i], sinus[i]), 5).draw(oled);
		oled.flush();
		hwlib::wait_ms(5);
	}
	
	for (int i = 0; i < 90; i++){
			cosvalues[i] = scale * cos(radians_from_degrees(i)) + centrex;
			sinvalues[i] = scale * sin(radians_from_degrees(i)) + centrey;
			
			cosvalues[i +90] = scale * cos(radians_from_degrees(i)) + centrex;
			sinvalues[i +90] = (scale * sin(radians_from_degrees(i)) *-1) + centrey;
			
			cosvalues[i +180] = (scale * cos(radians_from_degrees(i)) *-1) + centrex;
			sinvalues[i +180] = scale * sin(radians_from_degrees(i)) + centrey;
			
			cosvalues[i +270] = (scale * cos(radians_from_degrees(i)) *-1) + centrex;
			sinvalues[i +270] = (scale * sin(radians_from_degrees(i)) *-1) + centrey;
		}

	
	/*hwlib::circle(hwlib::location(locations.cosvalues[45], locations.sinvalues[45]), 5).draw(oled);
	hwlib::cout<< locations.cosvalues[45]<< " " << locations.sinvalues[45] << hwlib::endl;
	
	hwlib::circle(hwlib::location(locations.cosvalues[179], locations.sinvalues[179]), 5).draw(oled);
	hwlib::cout<< locations.cosvalues[179]<< " " << locations.sinvalues[179] << hwlib::endl;
	
	hwlib::circle(hwlib::location(locations.cosvalues[180], locations.sinvalues[180]), 5).draw(oled);
	hwlib::cout<< locations.cosvalues[180]<< " " << locations.sinvalues[180] << hwlib::endl;
	*//*draw_circle_circle(origin, 25, angles, 3, oled);*/
	oled.flush();
}

template <typename T, int amount>
class lookup_table{
private:
	T values [ amount ];
public:
	template<typename F>
	constexpr lookup_table( F function )
	{
		(for int i = 0; 1 < amount; i++)
		{
			values [ i ] = function (i)
		}
	}
	
	constexpr T get (int n) const {
		return valuse [n];
	}
	
};