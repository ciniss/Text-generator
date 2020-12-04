#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <ctime>
#include <random>
#include <string>
#include <chrono>
/*nessesary includes iostream/string,sstream, fstream,ctime, random,unordered_map, vector*/
class TextGenerator{
private:
	std::unordered_map<string, vector<string>> data;
	//std::map<string, vector<string>> data;
	std::vector<std::string>rawData;
public:
	TextGenerator(){
		srand((int)time(0));
	}
	///Loading data into the temporary buffor
	void load(const string& filepath){
		std::stringstream ss;
		std::string line;
		std::fstream file;
		file.open(filepath);
		if(file.good()){
			while(std::getline(file,line)){
				for(unsigned int i =0;i<line.size();i++) {
					char _char=line[i];
					if(i==line.size()-1){
						ss<<_char;
						rawData.push_back(ss.str());
						ss.str(string());
					}else{
					if(_char!=' '){
						ss<<_char;
					}
					else{
						rawData.push_back(ss.str());
						ss.str(string());
					}}
				}
			}
		}
		else{std::cout<<"Failed to load '"<<filepath<<"' file"<<std::endl;}
	}
	///Proccessing data into the map, either ordered or not
	/*
	ABCDBACADA
	A B C D 
	-------
 	B C D B
 	C A A A	
	D
	*/
	void proccessData(){
		std::string first=rawData[0], second;
		data[first]={};
		for(unsigned int i=1;i<rawData.size();i++ ){
			std::string word=rawData[i];
			if(data.find(word)==data.end()){
				//Dodawanie do mapy
				second=word;
				data[word]={};	
				data[first].push_back(word);
			}
			else{
				second=word;
				data[first].push_back(second);
			}
			first=second;
		}	
		rawData.clear();
	}
	template<typename T>
	static T getRandomElement(std::vector<T> arr){
		unsigned int r=arr.size(); 
		r=rand()%r;
		return arr[r];
	}
	//Generating text using markov chains.
	string generate(unsigned int length){
		std::string result="";
		std::string word=rawData[0];
		for(unsigned int i =0 ; i<length;i++){
			if(data[word].size()!=0){
				string temp=getRandomElement(data[word]);
				result +=word;
				result+=' ';
				word=temp;
			}
		}
		return result;
	}
};
int main(){
	std::cout<<"Text Generator v0.01"<<std::endl;
	std::cout<<"Text length:";
	unsigned int l;
	std::cin>>l;
	/*usage
	TextGenerator t;
	t.load(filename);
	t.proccess();
	std::string s = t.generate(length);*/
	
	std::cout<<"Filename: ";
	string f;
	std::cin>>f;
	TextGenerator gen;
	f="hungergames.txt";
	
	auto start=std::chrono::steady_clock::now();
	
	gen.load(f);
	gen.proccessData();
	std::cout<<"Result:\n\n";
	std::cout<<gen.generate(l)<<estd::ndl;
	
	//time control stuff
	auto end=std::chrono::steady_clock::now();
	std::chrono::duration<double> timeElapsed = end-start;
	std::cout<<"Generatin took: "<<timeElapsed.count()<<" seconds "<<std::endl;
	
	std::cout<<"\nThank you for using TextGenerator"<<std::endl;
}
