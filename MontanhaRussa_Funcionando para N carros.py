import _thread as thread
import queue
import time
import threading
import random


C = 4  # numero de vagas no carrinho
M = 3 # Numero de carros
N = 92  # Numero de passageiros
NUM = 1  # contador
P = 0   # ID do passageiro
tp = 0  #tempo de chegada do passageiro

vaga_carrinho = threading.Semaphore(0)
carro_0 = threading.Semaphore(0)
carro_1 = threading.Semaphore(0)
carro_2 = threading.Semaphore(0)
carrinho = threading.Semaphore(0)
fila_carrinho = threading.Semaphore(0)


class Queue(object):        #estrutura para criação da fila
    def __init__(self):
        self.data = []

    def add(self, item):
        self.data.append(item)

    def size(self):
        return len(self.data)

    def removeFila(self):
        try:
            self.data.pop(0)
        except IndexError:
            pass

    def removeFila2(self):
        try:
            self.data.pop(0)
        except IndexError:
            pass

car_queue = Queue()
passengers = []
passenger_queue = Queue()


def MontanhaRussa(N):
    global P
    global tp
    global th
    global carId

    for i in range(M):
        carId = i
        cart = threading.Thread(target=Carro)                               # criando thread carrinho
        car_queue.add(carId)
        cart.start()

    for i in range(N):                                                          # variavel N serve como contador
        P += 1                                                                  # numero sequencial de identificação pra cada thread
        th = threading.Thread(target=Passageiro)                                # criação da thread
        tp = random.randint(1,3)                                                # gerador de tempo aleatorio para chegada dos passageiros na fila
        time.sleep(tp)
        passenger_queue.add(P)                                                  # adiciona passageiro ao final da fila
        th.start()                                                              # inicia a thread

def Passageiro():

    id=P                                                                        # cria uma identificação individual pra cada thread
    if carro_0._value > 0:
        print("passageiro", P, "entrou na fila", tp, "s")
        carro_0.acquire()                                                     # passageiro decrementa uma vaga no carrinho
        print("passageiro", id, "entrou no carro 0")
        passenger_queue.removeFila()                                                # ao entrar no carrinho o passageiro é removido da fila
    elif carro_1._value > 0:
        print("passageiro", P, "entrou na fila", tp, "s")
        carro_1.acquire()  # passageiro decrementa uma vaga no carrinho
        print("passageiro", id, "entrou no carro 1")
        passenger_queue.removeFila()  # ao entrar no carrinho o passageiro é removido da fila
    elif carro_2._value > 0:
        print("passageiro", P, "entrou na fila", tp, "s")
        carro_2.acquire()  # passageiro decrementa uma vaga no carrinho
        print("passageiro", id, "entrou no carro 2")
        passenger_queue.removeFila()  # ao entrar no carrinho o passageiro é removido da fila


def Carro():

    carid = carId
    volta=0
    while (NUM < N):                                                            # montanha russa funcionando ate acabar os passageiros
        print("---------      EMBARCANDO NO CARRO",carid,"      ----------")
        if carid == 0:
            for i in range(C):
                carro_0.release()                                             # Liberando vagas no carrinho
                time.sleep(0.2)                                                     # esse delay evita que no terminal saia o resultado poluido
            while (carro_0._value > 0):                                       # se o carrinho ainda tiver vaga, ele vai ficar conferindo o numero de vaga disponivel
                time.sleep(2)
        elif carid == 1:
            for i in range(C):
                carro_1.release()                                             # Liberando vagas no carrinho
                time.sleep(0.2)                                                     # esse delay evita que no terminal saia o resultado poluido
            while (carro_1._value > 0):                                       # se o carrinho ainda tiver vaga, ele vai ficar conferindo o numero de vaga disponivel
                time.sleep(2)
        elif carid == 2:
            for i in range(C):
                carro_2.release()                                             # Liberando vagas no carrinho
                time.sleep(0.2)                                                     # esse delay evita que no terminal saia o resultado poluido
            while (carro_2._value > 0):                                       # se o carrinho ainda tiver vaga, ele vai ficar conferindo o numero de vaga disponivel
                time.sleep(2)
        print("\n--------------------------------------------------")
        print("Vagas no carrinho neste momento:", vaga_carrinho._value)         # Apenas para conferir se o carrinho zerou as vagas
        volta += 1
        print("Volta de numero:", volta,"carro:", carid)                                        # conferir se o carrinho ta dando o numero de voltas correto
        print("Atualizando fila:", passenger_queue.data)                        # mostrar quais passageiros estao na fila
        print("--------------------------------------------------")
        print("\n               ---CARRO", carid,"SAINDO---                ")
        time.sleep(10)                                                          # tempo de viagem do carro
        print("                 --CARRO", carid,"PAROU--                 \n")            # Carrinho para e inicia o processo de desembarque dos passageiros
        print("Atualizando fila:", passenger_queue.data)                        # mostrar quais passageiros estao na fila
        print("         Passageiros desembarcando do carro       ")
        for i in range(C):
            print("Passageiro saiu do carro")                                   # carrinho é esvaziado no inicio do While
        if passenger_queue.size() == 0:                                         # se nao houver mais passgeiro o carro desliga
            return 0
        print("==================================================")
        print("                   Nova volta                   \n")


    print("montanha russa parou")



MontanhaRussa(N)  # Inicia a Montanha Russa
