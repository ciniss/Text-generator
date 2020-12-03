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

using namespace std;
class TextGenerator{
private:
	bool debug;
public:
	//unordered_map<string, vector<string>> data;
	map<string, vector<string>> data;
	vector<string>rawData;
	TextGenerator(){
		srand((int)time(0));
		debug=false;
	}
	void setDebug(bool option){
		debug=option;
	}
	void load(const string& filepath){
		stringstream ss;
		string line;
		fstream file;
		file.open(filepath);
		if(file.good()){
			while(getline(file,line)){
				for(unsigned int i =0;i<line.size();i++) {
					char _char=line[i];
					if(i==line.size()-1){
						ss<<_char;
						rawData.push_back(ss.str());
						if(debug)cout<<"'"<<ss.str()<<"' word added to raw data array."<<endl;
						ss.str(string());
					}else{
					if(_char!=' '){
						ss<<_char;
					}
					else{
						rawData.push_back(ss.str());
						if(debug)cout<<"'"<<ss.str()<<"' word added to raw data array."<<endl;
						ss.str(string());
					}}
				}
			}
		}
		else{cout<<"Failed to load '"<<filepath<<"' file"<<endl;}
	}
	void proccessData(){
		if(debug)cout<<"\n\n\n"<<endl;
		string first=rawData[0], second;
		data[first]={};
		if(debug)cout<<"data['"<<first<<"'] was pushed to the map as a key"<<endl;
		for(unsigned int i=1;i<rawData.size();i++ ){
			string word=rawData[i];
			if(data.find(word)==data.end()){
				//Dodawanie do mapy
				second=word;
				data[word]={};	
				data[first].push_back(word);
				if(debug)cout<<"'"<<word<<"' was added as a key to the data"<<" AND "<<"data['"<<first<<"'].push_back('"<<word<<"')\n";
			}
			else{
				second=word;
				data[first].push_back(second);
				if(debug)cout<<"data['"<<first<<"'].push_back('"<<second<<"')\n";
			}
			first=second;
		}	
		//rawData.clear();
	}
	template<typename T>
	static T getRandomElement(vector<T> arr){
		unsigned int r=arr.size(); 
		r=rand()%r;
		return arr[r];
	}
	string generate(unsigned int length){
		string result="";
		string word=rawData[0];
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
	cout<<"Text Generator v0.01"<<endl;
	cout<<"Text length:";
	unsigned int l;
	//cin>>l;
	l=250;
	TextGenerator gen;
	gen.setDebug(false);
	cout<<"Filename: ";
	string f;
	//cin>>f;
	f="hungergames.txt";
	{
	auto start=chrono::steady_clock::now();
	gen.load(f);
	auto end=chrono::steady_clock::now();
	chrono::duration<double> timeElapsed = end-start;
	cout<<"Loading took: "<<timeElapsed.count()<<" seconds "<<endl;
	}

	{
	auto start=chrono::steady_clock::now();
	gen.proccessData();
	auto end=chrono::steady_clock::now();
	chrono::duration<double> timeElapsed = end-start;
	cout<<"Initial proccessing took: "<<timeElapsed.count()<<" seconds "<<endl;
	}
	cout<<"Result:\n\n";
	{
	auto start=chrono::steady_clock::now();
	cout<<gen.generate(l)<<endl;
	auto end=chrono::steady_clock::now();
	chrono::duration<double> timeElapsed = end-start;
	cout<<"Generatin took: "<<timeElapsed.count()<<" seconds "<<endl;
	}
	cout<<"\nThank you for using TextGenerator"<<endl;
	cout<<"Raw data size= "<<gen.rawData.size()<<endl;
}
