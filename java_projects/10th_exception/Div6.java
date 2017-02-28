

/* java Div 6 2
 * 6/2=3
 */

public class Div6 {

	public static void main(String args[]) {
		int m = Integer.parseInt(args[0]);
		int n = Integer.parseInt(args[1]);
		int r = 0;
		
		System.out.println("Begin of div");
		try {
			r = div(m, n);
		} catch (ArithmeticException e) {
			System.out.println("main :"+e);
		}
		System.out.println("End of div");

		System.out.println(m+"/"+n+"="+r);
		
	}

	public static int div(int m, int n) throws ArithmeticException {
		
		int r = 0;

		try {
			r = m / n;
		} catch (ArithmeticException e) {
			System.out.println("div :"+e);
			throw e;
		}
		return r;
	}
}

