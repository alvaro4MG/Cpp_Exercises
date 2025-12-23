import java.lang.Math; // para random

public class lamport extends Thread {
    static int n = 1;
    static volatile int choosing[] = {0,0};
    static volatile int number[] = {0,0};
    int id1; // identificador del hilo
    int id2; // identificador del otro hilo

    public void run() {
        try {
            for(;;){
                choosing[id1] = 1;
                number[id1] = 1 + Math.max(number[id1], number[id2]);
                choosing[id1] = 0;
                
                for(int i = 0; i < 2; i++){
                    while(choosing[id2] == 1);
                    while( (number[id2] > 0) && (number[id2] < number[id1]) ||
                            (number[id2] == number[id1]) && (id2 < id1) );
                }
                
                //sleep((long)(100*Math.random()));
                n = n + 1;
                System.out.println("En hilo "+id1+", n = "+n);

                choosing[id1] = 0;
            }
        }
        //catch( InterruptedException e ){return;}
        catch( Exception e ){return;}
    }

    lamport(int id) {
        this.id1 = id;
        this.id2 = (id == 1)? 0 : 1;
    }

    public static void main(String args[]) {
        Thread thr1 = new lamport(0);
        Thread thr2 = new lamport(1);

        thr1.start();
        thr2.start();
    }
}