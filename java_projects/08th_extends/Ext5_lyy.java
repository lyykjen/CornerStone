class Father {
	private int money;	

	public int getMoney() {return money; }
	public void setMoney(int money) {this.money = money; }

	public void printInfo() {System.out.println("This is Father");}

	private void printInfo2() {System.out.println("This is Father");}
}

class Son extends Father{
	
	private int a;//lyy
	
	public void printInfo() {System.out.println("This is son");}

	public void printInfo2() {System.out.println("This is Father");}
	
	public void printInfo3() {System.out.println(a);}//lyy
	public void seta(int a) {this.a = a;}//lyy
	
}

public class  Ext5_lyy {
	public static void main (String args[]) {
		Son son = new Son();
		son.setMoney(100);
		//son.printInfo();
		
		System.out.println(son.getMoney());//lyy
		son.seta(8);//lyy
		son.printInfo3();//lyy
		
	}
}

