package rtrk.pnrs.jniexample;


public class FibonacciNative {

    private static final double GOLDEN_RATIO = 1.6180339887;
    private static final double SQRT_5 = 2.236067977;
    public static native int getFebonacci(int n);

    static { 
        System.loadLibrary("fibonacci");
    } 

    public int get(int n) {
        return getFebonacci(n);
        //return (int) Math.floor(Math.pow(GOLDEN_RATIO, n)/SQRT_5 + 0.5);
    }

}
