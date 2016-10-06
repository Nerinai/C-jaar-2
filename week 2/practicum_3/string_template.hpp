#ifndef STRING_TEMPLATE_HPP
#define STRING_TEMPLATE_HPP
#ifndef STRING_PANIC_FUN
#define STRING_PANIC_FUN [](){ while (true);}
#endif
#include <iostream>
#include <cstdlib>


template <size_t size>
class string_template
{
	size_t index = 0;
	char string[size +1] = { };
public:
	string_template() = default;
	
	template <size_t size2>
	string_template(const string_template<size2>& str):
	index(), string()
	{
		*this += str.c_str();
	}
	
	string_template(char str):
	index(), string()
	{
		char array[2] = {str, '\0'};
		*this += array;
		
	}
	
	string_template(const char * str):
	index(), string()
	{
		*this += str;
		//int i = 0;
		//while (*str != '\0'){
		//	string[i] = *str;
		//	i++;
		//	str++;
		//}
		//string[i+1] = '\0';
		//index = i;*/
	}
	
	~string_template() = default;
	
	
	size_t length() const {
		return index;
	}

	char * c_str(){
		return string;
	}

	const char * c_str() const {
		return string;
	}


	const char& operator [] (const size_t ind) const{
		if ((ind > index) || (ind < 0)){
			panic();
		}
		return string[ind];
	}

	char& operator [] (const size_t ind){
		if ((ind > index) || (ind < 0)){
			panic();
		}
		return string[ind];
	}

	void panic(){
		//std::cout << "PANIC" << std::endl;
		STRING_PANIC_FUN();
	}
	
	void clear(){
		index = 0;
		string[0] = '\0';
	}

	const string_template& operator += (const string_template& str){
		
		*this += str.c_str();
		
	return *this;
	}
	
	const string_template& operator += (char str){
		
		const char whoop[2] = {str, '\0'};
		
		return *this += whoop;
	}
	
	const string_template& operator += (const char * str){
	const char * base_addr = str;
	size_t ind = 0;
	while ((*str != '\0') && (ind < size)){
		ind++;
		str++;
	}
	
	str = base_addr;
	
	for(size_t i = ind; i > 0; i--){
			string[index] = * str;
			index++;
			str++;
	}
	string[index] = '\0';
	return *this;
	}
	
	
	const string_template& operator = (const char * str){
		clear();
		return *this += str;
	}
	
	const string_template& operator = (const string_template& str){
		clear();
		return *this += str.c_str();
	}

	const string_template& operator = (char str){
		clear();
		
		return *this += str;
	}
	
	//template<typename ret>
	//ret& operator << (ret& stream,const string_template& str) const {
	//return stream << str.c_str();
	//}
	
};

template<typename ret, size_t size>
	ret& operator << (ret& stream, const string_template<size>& str){
		return stream << str.c_str();
}

#endif // STRING_TEMPLATE_HPP
