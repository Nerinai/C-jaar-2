#include <stdio.h>

int main(int argc, char **argv)
{
	enum toestand_t {magomlaag, magnietomlaag, wachten};
	
	toestand_t currentsituation = magomlaag;
	
	while (true){
		event e = retrieveevent():
		switch (currentsituation){
			case magomlaag : if (e.src = windsensor && e.value >= 5){
				currentsituation = magnietomlaag;
			}
			break;
			
			case magnietomlaag : if (e.scr = windsensor && 	e.value < 5) {
				currentsituation = wachten;
				timer.start(5 min);
			}
			break;
			
			case wachten : 
				if (e.scr = windsensor && e.value >= 5){
					currensituation = magnietomlaag;
					timer.stop();
				}
				if (e.src = timer)
					currentsituation = magomlaag;
				break;
				
		}
	}
	return 0;
}
