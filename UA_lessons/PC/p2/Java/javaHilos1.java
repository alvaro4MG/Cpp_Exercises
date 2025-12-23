class ThreadConHerencia extends Thread {
    String palabra;
 
    public ThreadConHerencia (String p) {
        palabra=p;
    }
 
    public void run() {
        for (int i=0; i < 10 ; i++) {
            System.out.println(palabra);
        }
    }
 
    public static void main(String[]args){
        Thread a=new ThreadConHerencia("hilo1");
        Thread b=new ThreadConHerencia("hilo2");
 
        a.start();
        b.start();

        try{
            a.join();
            b.join();
        }catch(InterruptedException e){
            System.out.println("Error esperando al hilo");
        }

        System.out.println("Fin del hilo principal");
    }
}