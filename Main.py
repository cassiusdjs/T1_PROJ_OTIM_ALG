import matplotlib.pyplot as plt


class String:
    def __init__(self, valor):
        self.valor = valor
        self.tam = len(valor)


class StringSearchAlgorithms:
    def __init__(self):
        self.iteracoes = 0

    def rabin_karp(self, entrada, comparacao):
        d = 256
        q = 13
        m = comparacao.tam
        n = entrada.tam
        h = pow(d, m - 1) % q
        p = 0
        t = 0
        self.iteracoes = 0

        if m > n:
            return -1

        for i in range(m):
            p = (d * p + ord(comparacao.valor[i])) % q
            t = (d * t + ord(entrada.valor[i])) % q
            self.iteracoes += 1

        for s in range(n - m + 1):
            if p == t:
                match = True
                for i in range(m):
                    self.iteracoes += 1
                    if entrada.valor[s + i] != comparacao.valor[i]:
                        match = False
                        break
                if match:
                    return s
            if s < n - m:
                t = (t - h * ord(entrada.valor[s])) % q
                t = (t * d + ord(entrada.valor[s + m])) % q
                t = (t + q) % q
            self.iteracoes += 1

        return -1

    def knuth_morris_pratt(self, entrada, comparacao):
        self.iteracoes = 0
        M = comparacao.tam
        N = entrada.tam
        lps = [0] * M
        j = 0
        i = 1

        while i < M:
            self.iteracoes += 1
            if comparacao.valor[i] == comparacao.valor[j]:
                j += 1
                lps[i] = j
                i += 1
            elif j != 0:
                j = lps[j - 1]
            else:
                lps[i] = 0
                i += 1

        i = 0
        j = 0

        while i < N:
            self.iteracoes += 1
            if comparacao.valor[j] == entrada.valor[i]:
                i += 1
                j += 1

            if j == M:
                j = lps[j - 1]
                return i - j

            elif i < N and comparacao.valor[j] != entrada.valor[i]:
                if j != 0:
                    j = lps[j - 1]
                else:
                    i += 1

        return -1


class GraphGenerator:
    def __init__(self, algorithm, directory):
        self.algorithm = algorithm
        self.directory = directory

    def generate_graph(self, entrada, comparacao):
        sizes = list(range(100, 1001, 100))
        counts = []

        for size in sizes:
            entrada.valor = 'a' * size + 'test'
            entrada.tam = len(entrada.valor)

            algorithm_instance = StringSearchAlgorithms()
            algorithm_method = getattr(algorithm_instance, self.algorithm)

            algorithm_method(entrada, comparacao)
            counts.append(algorithm_instance.iteracoes)

        plt.plot(sizes, counts, label=self.algorithm)
        plt.xlabel('Input size')
        plt.ylabel('Iterations')
        plt.legend()
        plt.savefig(self.directory)
        plt.show()


if __name__ == "__main__":
    entradaA = String('ABCDCBDCBDACBDABDCBADF')
    entradaB = String('A' * 500000 + 'B')
    comparacao = String('ADF')

    algorithms = StringSearchAlgorithms()

    graph_generator_rabin_karp1 = GraphGenerator('rabin_karp', 'C:/Users/cassi/OneDrive - PUCRS - BR/Faculdade/V '
                                                               'Semestre/Projeto e Otimização de '
                                                               'Algoritmos/Atividades/T1/Rabin_Karp_ADF.jpg')
    graph_generator_rabin_karp1.generate_graph(entradaA, comparacao)

    graph_generator_rabin_karp2 = GraphGenerator('rabin_karp', 'C:/Users/cassi/OneDrive - PUCRS - BR/Faculdade/V '
                                                               'Semestre/Projeto e Otimização de '
                                                               'Algoritmos/Atividades/T1/Rabin_Karp_500000.jpg')
    graph_generator_rabin_karp2.generate_graph(entradaB, comparacao)

    graph_generator_kmp1 = GraphGenerator('knuth_morris_pratt', 'C:/Users/cassi/OneDrive - PUCRS - BR/Faculdade/V '
                                                            'Semestre/Projeto e Otimização de '
                                                            'Algoritmos/Atividades/T1/Knuth_ADF.jpg')
    graph_generator_kmp1.generate_graph(entradaA, comparacao)

    graph_generator_kmp2 = GraphGenerator('knuth_morris_pratt', 'C:/Users/cassi/OneDrive - PUCRS - BR/Faculdade/V '
                                                            'Semestre/Projeto e Otimização de '
                                                            'Algoritmos/Atividades/T1/Knuth_500000.jpg')
    graph_generator_kmp2.generate_graph(entradaB, comparacao)
