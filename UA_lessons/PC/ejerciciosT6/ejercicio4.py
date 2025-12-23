#Problema cuenta de ahorros

import threading
from random import seed
from random import randint

THREADS = 10
ITERACIONES = 10


class Monitor:
    def __init__(self, balance):
        self.balance = balance
        self.mutex = threading.Lock()
        self.sacar = threading.Condition(self.mutex)

    def depositar(self, cantidad):
        with self.mutex:
            print(f"Voy a depositar: {cantidad}")
            self.balance += cantidad
            print(f"Balance tras depositar: {self.balance}")
            self.sacar.notifyAll()          #Avisa a todos

    def devolver(self, cantidad):
        with self.mutex:
            print(f"Voy a sacar: {cantidad}")
            while self.balance < cantidad:   #evitar valores negativos y permite colarse
                self.sacar.wait()
            self.balance -= cantidad
            print(f"Balance tras sacar: {self.balance}")

def depositador(m):
    for j in range(ITERACIONES):
        value = randint(1,100)
        m.depositar(value)

def sacador(m):
    for j in range(ITERACIONES):
        value = randint(1,80)
        m.devolver(value)

def main():
    seed(1)
    m = Monitor(0)

    threads = []
    for i in range(THREADS):
        # Crea los nuevos hilos, mitad para meter dinero y mitad para sacar
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