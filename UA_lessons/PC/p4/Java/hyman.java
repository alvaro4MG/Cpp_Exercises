import java.lang.Math; // para random

public class hyman extends Thread {
    static int n = 1;
    static volatile int turno = 0;
    static volatile int C[] = {0,0};
    int id1; // identificador del hilo
    int id2; // identificador del otro hilo

    public void run() {
        try {
            for(;;){
                turno = id1;
                C[id1] = 1;

                while(turno != id1){
                    while(C[id2] == 1);
                    turno = id1;
                }

                //sleep((long)(100*Math.random()));
                n = n + 1;
                System.out.println("En hilo "+id1+", n = "+n);

                C[id1] = 0;
            }
        }
        //catch( InterruptedException e ){return;}
        catch( Exception e ){return;}
    }

    hyman(int id) {
        this.id1 = id;
        this.id2 = (id == 1)? 0 : 1;
    }

    public static void main(String args[]) {
        Thread thr1 = new hyman(0);
        Thread thr2 = new hyman(1);

        thr1.start();
        thr2.start();
    }
}