# Análise de Complexidade de Algoritmos de Ordenação

Uma impressionante ferramenta de visualização web para analisar e comparar a complexidade computacional de seis algoritmos clássicos de ordenação. Este projeto combina C para execução de experimentos de alto desempenho com React para uma visualização de dados bonita e interativa.

![Project Banner](https://img.shields.io/badge/C-Algorithms-00599C?style=for-the-badge&logo=c) ![React](https://img.shields.io/badge/React-Visualization-61DAFB?style=for-the-badge&logo=react) ![Vite](https://img.shields.io/badge/Vite-Build_Tool-646CFF?style=for-the-badge&logo=vite)

## 📊 Funcionalidades

- **6 Algoritmos de Ordenação**: Bubble Sort, Insertion Sort, Heap Sort, Merge Sort, Quick Sort e Radix Sort
- **Análise Empírica**: 30 execuções por tamanho de array para validade estatística
- **Gráficos Interativos**: Ative/desative algoritmos, alterne entre métricas de comparações/trocas
- **Interface Moderna**: Tema escuro, design responsivo, animações suaves
- **Implantável na Web**: Construído com React e Recharts para fácil implantação

## 🚀 Início Rápido

### Pré-requisitos

- Compilador GCC (para código C)
- Node.js e npm (para visualização React)
- Make (ferramenta de compilação)

### 1. Execute o Experimento

```bash
# Compile e execute a análise de ordenação
make run
```

Isso irá:
- Compilar o código C
- Executar experimentos para arrays de tamanho 1-1000
- Gerar 30 execuções por tamanho
- Salvar resultados em `results/data.json`

O experimento leva alguns minutos. Você verá o progresso em tempo real:
```
Progress: 450/606 (74.3%) - Size: 750, Algorithm: Heap Sort
```

### 2. Inicie a Visualização

```bash
cd visualization

npm run copy-results

npm run dev
```

Abra seu navegador em `http://localhost:5173` e aproveite os gráficos interativos!

## 📁 Estrutura do Projeto

```
├── src/                    # Código-fonte C
│   ├── sorting.h          # Cabeçalhos dos algoritmos
│   ├── sorting.c          # Todas as 6 implementações
│   └── experiment.c       # Executor de experimentos
├── visualization/         # App React
│   ├── src/
│   │   ├── App.jsx       # Componente principal com gráficos
│   │   └── App.css       # Estilos
│   └── public/
│       └── results/      # Arquivos de dados (copiados de ../results)
├── results/              # Saída dos experimentos
│   └── data.json        # Arquivo de dados gerado
├── build/               # Binários C compilados
└── Makefile            # Configuração de compilação
```

## 🎯 Algoritmos Analisados

| Algoritmo | Complexidade de Tempo (Média) | Complexidade de Espaço | In-place? |
|-----------|-------------------------------|------------------------|-----------|
| Bubble Sort | O(n²) | O(1) | ✅ |
| Insertion Sort | O(n²) | O(1) | ✅ |
| Heap Sort | O(n log n) | O(1) | ✅ |
| Merge Sort | O(n log n) | O(n) | ❌ |
| Quick Sort | O(n log n) | O(log n) | ✅ |
| Radix Sort | O(nk) | O(n + k) | ❌ |

## 📈 Métricas Rastreadas

- **Comparações**: Número de vezes que dois elementos são comparados
- **Trocas**: Número de vezes que elementos são movidos/copiados na memória

## 🛠️ Comandos de Compilação

```bash
# Compilar o experimento C
make

# Compilar e executar o experimento
make run

# Limpar arquivos de compilação e resultados
make clean

# Mostrar ajuda
make help
```

## 🎨 Personalização

### Modificar Tamanhos de Array

Edite `src/experiment.c`:
```c
#define MAX_SIZE 1000    // Tamanho máximo do array
#define STEP_SIZE 10     // Incremento de tamanho
```

### Alterar Número de Execuções

Edite `src/experiment.c`:
```c
#define NUM_TRIALS 30    // Execuções por tamanho
```

### Personalizar Cores

Edite `visualization/src/App.jsx`:
```javascript
const COLORS = {
  'Bubble Sort': '#ef4444',
  'Insertion Sort': '#f59e0b',
  // ... personalize as cores
}
```

## 📊 Resultados de Exemplo

A visualização mostra padrões claros:
- **Bubble & Insertion Sort**: Crescimento quadrático (O(n²))
- **Heap, Merge & Quick Sort**: Crescimento logarítmico (O(n log n))
- **Radix Sort**: Crescimento linear (O(n)) para tamanhos fixos de dígitos