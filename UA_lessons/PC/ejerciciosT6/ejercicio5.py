#Problema de los canibales

import threading

THREADS = 10
CANIBALES = 5
ITERACIONES = 3
MISIONEROS = 5

class Monitor:
    def __init__(self, olla):
        self.olla = olla
        self.mutex = threading.Lock()
        self.espera = threading.Condition(self.mutex)
        self.coci = threading.Condition(self.mutex)

    def cocinar(self):
        with self.mutex:
            while self.olla > 0:
                self.coci.wait()
            print('Voy a cocinar')
            self.olla = MISIONEROS
            self.espera.notify_all()

    def comer(self):
        with self.mutex:
            while self.olla < 1:
                self.coci.notify()
                self.espera.wait()
            self.olla -= 1
            print(f"El canibal ha comido. Olla: {self.olla}")
            self.coci.notify_all()

def cocinero(m):
    for j in range(ITERACIONES):
        m.cocinar()

def canibal(m):
    for j in range(ITERACIONES):
        m.comer()

def main():
    m = Monitor(MISIONEROS)

    threads = []
    t = threading.Thread(target=cocinero, args=(m,))
    threads.append(t)
    t.start()

    for i in range(CANIBALES):
        t = threading.Thread(target=canibal, args=(m,))
        threads.append(t)
        t.start()

    for t in threads:
        t.join()



if __name__ == "__main__":
    main()