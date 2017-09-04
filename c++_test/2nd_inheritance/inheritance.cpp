#include <iostream>
#include <string.h>
#include <unistd.h>


using namespace std;

class Leader//基类,也叫父类
{
	private:
		int money = 0;
		void leading_skill(){
			cout << "teacher's leading skill" << endl;		
			set_money(1000);
		}
	protected:
		int office_key;
	public:
		int tools = 0;
		void common_skill(){
			cout << "teacher's common skill" << endl;		
			set_money(100);
		}
		int get_money(){
			return money;
		}
		void set_money(int money){
			this->money = money;
		}		
};

class Worker : public Leader//派生类,也叫子类(public)
{
	private:
		int pocket_money;		
	public:
		using Leader::office_key;
			
		void labor(){
			cout << "worker's labor" << endl;
			office_key = 1;
			int  m = get_money() -90;
			set_pocket_money(m);
			
		}
		void set_money(int money){
			pocket_money = money;
		}
		int get_pocket_money(){
			return pocket_money;
		}
		void set_pocket_money(int pocket_money){
			this->pocket_money = pocket_money;
		}
};

class Worker_pro : protected Leader//派生类,也叫子类(protected)
{
	private:
		int pocket_money;		
	public:
		using Leader::office_key;
			
		void labor(){
			cout << "worker's labor" << endl;
			office_key = 1;
			int  m = get_money() -90;
			set_pocket_money(m);
			
		}
		void set_money(int money){
			pocket_money = money;
		}
		int get_pocket_money(){
			return pocket_money;
		}
		void set_pocket_money(int pocket_money){
			this->pocket_money = pocket_money;
		}
};

class Worker_son : public Worker//派生类的子类(public)
{	
	public:
		void test()
		{
			cout << "worker son's test" << endl;
			tools ++;
			cout << tools << endl;
		}
};

class Worker_son_pro : protected Worker//派生类的子类(protected)
{	
	public:
		void test()
		{
			cout << "worker son_pro's test" << endl;
			tools ++;
			cout << tools << endl;
		}
};

int main()
{
	Leader boss;
	boss.common_skill();
	
	Worker engineer;
	//engineer.set_money(100);
	engineer.common_skill();
	engineer.labor();
	
	cout << engineer.get_money() << endl;
	cout << engineer.get_pocket_money() << endl;
	cout << engineer.office_key << endl;//office_key is protected

	Worker_pro engineer_pro;
	//engineer_pro.common_skill();//error, protected member cannot be used by others publicly
	engineer_pro.labor();
	cout << engineer_pro.get_pocket_money() << endl;

	Worker_son wson;
	wson.test();
	wson.tools += 2;
	cout << wson.tools << endl;

	Worker_son_pro wson_pro;
	wson_pro.test();
	//wson_pro.tools += 2;//error:inaccessible, protected
	return 0;
}