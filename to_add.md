# Add the theorical part the explanation of time complexity of Merging Subtrees

Time Complexity of Merging Subtrees
The complexity can be demonstrated with the following problem:
    You have an list of NN ones and a counter initially set to 00. While the list has greater than one element, remove any two elements aa and bb from the list, add a⋅ba⋅b to the counter, and add a+ba+b to the list. In terms of NN, what is the maximum possible value of the counter at the end of this process?

Solution
The counter will always be equal to (N2)(2N​) at the end of this process; every pair of ones contributes one to the answer. Adding a⋅ba⋅b to the counter corresponds to merging two subtrees of sizes aa and bb into one subtree of size a+ba+b in O(ab)O(ab) time, which in total will result in a complexity of O(N2)O(N2).


# Rodar /build/run.sh toda vez que o caderno é commitado


# Mudar descrição da Dominator Tree para explicar melhor que é um "dominador" e o que seria a árvore dominadora

# Add code and description to Polynomial division

# Verificar e concertar o HLD

# Add code that generates Block Cut tree

# Adicionar comentários no Convex Hull para quando quiser fazer os pontos na extremidade do convexhull serem retornados também

# Atualizar Subset Sum com código para construir o vetor de frequencias {item, freq} dado uma lista de items normal

# Comentar Manacher