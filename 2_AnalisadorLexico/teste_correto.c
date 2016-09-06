
int main () {
    //queue<char> q;
    int i;
    int j;
    int k;
    i = 10;
    j = 1;
    k = 0;
    
    if (i >= j) {
	k = condicao(i, j);
    }
    
    // Aqui, o valor de i será igual ao número de elementos da pilha "q"
    /*while (i > 0) {
	q = q + 'i';
	i = i - 1;
    }*/
    
    return 0;
}

int condicao(int x, int y) {
    int z;
    if (x > y) {
        z = x + y;
    }
    else { // Aqui x == y
        z = 2*x;
    }
    
    return z;
}