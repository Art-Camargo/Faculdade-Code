# Resolução de Sistemas Lineares em Python (Gauss e Gauss-Jordan)

Este projeto implementa dois métodos clássicos de Álgebra Linear Numérica para resolver sistemas lineares representados por matriz aumentada:

- Eliminação de Gauss (com substituição regressiva)
- Eliminação de Gauss-Jordan (forma escalonada reduzida)

Arquivo principal do projeto:

- `gauss.py`

## 1. Procedimento de pesquisa e construção do código

Esta seção documenta o processo completo usado para estruturar o programa.

### 1.1 Levantamento do problema

Objetivo identificado:

- Resolver sistemas lineares de ordem `n` a partir de uma matriz aumentada `n x (n+1)`.
- Permitir dois fluxos de entrada:
  - sistemas prontos (pré-cadastrados)
  - entrada manual do usuário
- Exibir etapas intermediárias das operações de linha para fins didáticos.

### 1.2 Definição da abordagem algorítmica

Foram escolhidos dois algoritmos por serem padrão em disciplinas de Cálculo Numérico e Álgebra Linear:

- **Gauss**: triangularização + substituição regressiva.
- **Gauss-Jordan**: escalonamento até a forma reduzida por linhas, retornando diretamente a solução.

Além disso, foi aplicado **pivotamento parcial** em ambos os métodos para melhorar robustez numérica.

### 1.3 Requisitos funcionais implementados

- Validação de matriz aumentada em `validar_matriz_aumentada`.
- Escolha automática de pivô em `escolher_pivo`.
- Cópia profunda da matriz (`copy.deepcopy`) para não alterar a entrada original.
- Tratamento de singularidade/indeterminação com tolerância `EPS = 1e-12`.
- Impressão das etapas (`print_etapa`) para acompanhamento de cada operação.
- Menu interativo para seleção de sistema e método.

### 1.4 Construção do código por blocos

#### a) Utilitários de impressão

- `print_matrix(mat)`: formata saída com 2 casas decimais.
- `print_etapa(titulo, mat)`: imprime título + matriz.

Motivo: facilitar visualização didática das transformações de linha.

#### b) Validação estrutural da entrada

- `validar_matriz_aumentada(mat)` garante:
  - `mat` é lista não vazia
  - número de colunas é exatamente `n+1`

Motivo: impedir execução com formato inconsistente.

#### c) Estratégia de pivô

- `escolher_pivo(mat, i)` seleciona, na coluna `i`, a linha com maior valor absoluto a partir de `i`.

Motivo: reduzir risco de divisão por pivô pequeno e diminuir erro numérico acumulado.

#### d) Método de Gauss

Fluxo em `gauss(mat)`:

1. valida matriz
2. para cada coluna pivô:
   - faz pivotamento parcial
   - elimina elementos abaixo do pivô
3. executa substituição regressiva
4. retorna vetor solução

#### e) Método de Gauss-Jordan

Fluxo em `gauss_jordan(mat)`:

1. valida matriz
2. para cada pivô:
   - pivotamento parcial
   - normaliza linha pivô (pivô vira 1)
   - zera elementos acima e abaixo do pivô
3. retorna última coluna como solução

#### f) Interface de execução

- `main()` organiza o fluxo de uso:
  - seleção entre sistema pronto e manual
  - seleção entre Gauss e Gauss-Jordan
  - captura e exibição da solução
  - tratamento de erro com `try/except`

### 1.5 Critérios de robustez usados

- Tolerância numérica (`EPS`) para detectar pivôs praticamente nulos.
- Mensagens de erro para entradas inválidas e sistemas sem solução única.
- Verificação de método selecionado para evitar caminhos inválidos.

### 1.6 Limitações atuais

- Não classifica separadamente os casos:
  - sistema impossível
  - sistema possível indeterminado
- Não calcula residual `||Ax-b||` para validar qualidade da solução.
- Formatação de saída fixa em 2 casas decimais.

## 2. Como executar

Pré-requisito:

- Python 3 instalado

Execução:

```bash
python gauss.py
```

## 3. Estrutura do arquivo

Funções principais em `gauss.py`:

- `gauss(mat)`
- `gauss_jordan(mat)`
- `validar_matriz_aumentada(mat)`
- `escolher_pivo(mat, i)`
- `main()`

## 4. Referências consultadas

### 4.1 Referências efetivamente consultadas nesta construção

- Código-fonte local do projeto: `gauss.py`.
- Conhecimento algorítmico clássico de eliminação de Gauss/Gauss-Jordan e pivotamento parcial aplicado na implementação.

### 4.2 Tentativas de consulta externa nesta sessão

Foram feitas tentativas de consulta em páginas técnicas públicas, mas a recuperação de conteúdo foi interrompida no ambiente de execução. Links utilizados nas tentativas:

- https://en.wikipedia.org/wiki/Gaussian_elimination
- https://en.wikipedia.org/wiki/Gauss%E2%80%93Jordan_elimination
- https://en.wikipedia.org/wiki/Pivot_element#Partial_and_complete_pivoting

### 4.3 Bibliografia teórica recomendada

- BURDEN, Richard L.; FAIRES, J. Douglas. _Numerical Analysis_.
- CHAPRA, Steven C.; CANALE, Raymond P. _Numerical Methods for Engineers_.
- STRANG, Gilbert. _Introduction to Linear Algebra_.

## 5. Possíveis melhorias

- Implementar classificação de sistemas (SPD/SI/SPI).
- Adicionar checagem de residual e erro relativo.
- Incluir testes automatizados para os sistemas prontos.
- Permitir leitura de matrizes por arquivo (`.txt`/`.csv`).
