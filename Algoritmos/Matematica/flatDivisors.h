/**
 * Author: Gemini
 * Source: 
 * Description: Gera os divisores de todos os números até $n$ armazenados em um vetor simples.
 * Usage: build_flat_divisors(); for(int i = head[Y]; i < head[Y + 1]; ++i) int d = flat_divs[i];
 * Skip: true
 * Time: $O(N \log N)$.
 * Status: Meio-testado (CF)
 */

int div_count[MAXN + 1];   // Stores how many divisors each number has
int head[MAXN + 2];        // Stores the starting index in the flat array for each number
int current_pos[MAXN + 1]; // Used to track where to insert the next divisor
vector<int> flat_divs;     // The single flat array

void build_flat_divisors() {
    for(int i = 1; i <= MAXN; i++) {
        for(int j = i; j <= MAXN; j += i) {
            div_count[j]++;
        }
    }

    head[1] = 0;
    for(int i = 1; i <= MAXN; i++) {
        head[i + 1] = head[i] + div_count[i];
        current_pos[i] = head[i];
    }

    flat_divs.resize(head[MAXN + 1]);

    for(int i = 1; i <= MAXN; i++) {
        for(int j = i; j <= MAXN; j += i) {
            flat_divs[current_pos[j]++] = i;
        }
    }
}