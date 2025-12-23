#Problema cuenta de ahorros con variante

import threading
from random import seed
from random import randint

THREADS = 6
ITERACIONES = 5


class Monitor:
    def __init__(self, balance):
        self.balance = balance
        self.cola = 0
        self.puestoUltimo = 0
        self.depositos = 0
        self.mutex = threading.Lock()
        self.sacar = threading.Condition(self.mutex)
        self.esperar = threading.Condition(self.mutex)

    def getBalance(self):
        return self.balance

    def finDepositos(self):
        return (self.depositos == (THREADS/2*ITERACIONES))

    def depositar(self, cantidad):
        with self.mutex:
            print(f"Voy a depositar: {cantidad}")
            self.balance += cantidad
            #self.depositos += 1
            print(f"Balance tras depositar: {self.balance}")
            self.sacar.notify()
            #self.esperar.notify()

    def devolver(self, cantidad):
        with self.mutex:
            #self.esperar.wait()
            puestoCola = self.cola
            self.cola += 1
            print(f"Voy a sacar: {cantidad}. Tengo el puesto {puestoCola}")
            while puestoCola > self.puestoUltimo:
                self.esperar.wait()
            while self.balance < cantidad:
                self.sacar.wait()
            self.puestoUltimo += 1
            self.esperar.notify_all()
            #self.esperar.notify()
            self.balance -= cantidad
            print(f"Balance tras sacar: {self.balance}")

def depositador(m):
    for j in range(ITERACIONES):
        value = randint(1,20)
        m.depositar(value)
    #print('Depositador terminado')
    #if m.finDepositos():
        #m.balance += 1000

def sacador(m):
    for j in range(ITERACIONES):
        value = randint(1,10)
        m.devolver(value)
    #print('Sacador terminado')

def main():
    seed(1)
    m = Monitor(0)

    threads = []
    for i in range(THREADS):
        if i%2 == 0:
            t = threading.Thread(target=depositador, args=(m,))
        else:
            t = threading.Thread(target=sacador, args=(m,))
        threads.append(t)
        t.start()

    for t in threads:
        t.join()

    print("BALANCE TOTAL: {} \n".format(m.balance))


if __name__ == "__main__":
    main()