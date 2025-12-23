import java.lang.Math; // para random

public class dekker extends Thread {
    static int n = 1;
    static volatile int turno = 0;
    static volatile int C[] = {0,0};
    int id1; // identificador del hilo
    int id2; // identificador del otro hilo

    public void run() {
        try {
            for(;;){
                C[id1] = 1;
                while(C[id2] == 1){
                    if(turno == id2){
                        C[id1] = 0;
                        while(turno != id1);
                        C[id1] = 1;
                    }
                }
                
                //sleep((long)(100*Math.random()));
                n = n + 1;
                System.out.println("En hilo "+id1+", n = "+n);

                C[id1] = 0;
                turno = id2;
            }
        }
        //catch( InterruptedException e ){return;}
        catch( Exception e ){return;}
    }

    dekker(int id) {
        this.id1 = id;
        this.id2 = (id == 1)? 0 : 1;
    }

    public static void main(String args[]) {
        Thread thr1 = new dekker(0);
        Thread thr2 = new dekker(1);

        thr1.start();
        thr2.start();
    }
}