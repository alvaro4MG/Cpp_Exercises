class ThreadConRunnable implements Runnable {
    String palabra;
 
    public ThreadConRunnable (String p){
        palabra=p;
    }
 
    public void run() {
        for(int i=0;i<10;i++)
            System.out.println(palabra);
    }

    public static void main(String[]args){
        ThreadConRunnable a=new ThreadConRunnable("hilo1");
        ThreadConRunnable b=new ThreadConRunnable("hilo2");
 
        Thread t1=new Thread (a);
        Thread t2=new Thread (b);
 
        t1.start();
        t2.start();

        try{
            t1.join();
            t2.join();
        }catch(InterruptedException e){
            System.out.println("Error esperando al hilo");
        }
 
        System.out.println("Fin del hilo principal");
    }
}