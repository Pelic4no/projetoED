#include <stdio.h>
#include <stdlib.h>
#include "../include/finaliza.h"

// Verifica se a filial atende 100% do carrinho
int filial_apta(Carrinho *car, Loja *filial) {
    ItemCarrinho *item = car->inicio;
    while (item != NULL) {
        Estoque *e = filial->estoque;
        int encontrado = 0;
        while (e != NULL) {
            if (e->cod_prod == item->cod) {
                if (e->qtd < item->qtd)
                    return 0;
                encontrado = 1;
                break;
            }
            e = e->prox;
        }
        if (!encontrado)
            return 0;
        item = item->prox;
    }
    return 1;
}

// Ajusta o carrinho com base no estoque da filial
void ajusta_carrinho(Carrinho *car, Loja *filial) {
    ItemCarrinho *item = car->inicio;
    ItemCarrinho *anterior = NULL;
    while (item != NULL) {
        Estoque *e = filial->estoque;
        int disponivel = 0;

        while (e != NULL) {
            if (e->cod_prod == item->cod) {
                disponivel = e->qtd;
                break;
            }
            e = e->prox;
        }

        if (disponivel == 0) {
            car->total -= item->qtd * item->preco;
            if (anterior == NULL)
                car->inicio = item->prox;
            else
                anterior->prox = item->prox;
            free(item);
            item = (anterior == NULL) ? car->inicio : anterior->prox;
        } else if (disponivel < item->qtd) {
            car->total -= (item->qtd - disponivel) * item->preco;
            item->qtd = disponivel;
            anterior = item;
            item = item->prox;
        } else {
            anterior = item;
            item = item->prox;
        }
    }
}

// Abate o estoque da filial com os itens do carrinho
void abate_estoque(Carrinho *car, Loja *filial) {
    ItemCarrinho *item = car->inicio;
    while (item != NULL) {
        Estoque *e = filial->estoque;
        while (e != NULL) {
            if (e->cod_prod == item->cod) {
                e->qtd -= item->qtd;
                break;
            }
            e = e->prox;
        }
        item = item->prox;
    }
}
int finaliza(Carrinho *car, DBLojas *db, Catalogo *cat, int id_filial) {
    Loja *filial = db->inicio;
    while (filial != NULL && filial->id != id_filial)
        filial = filial->prox;

    if (filial == NULL) {
        printf("\nFilial não encontrada.\n");
        return 0;
    }

    if (!filial_apta(car, filial)) {
        ajusta_carrinho(car, filial);
        if (car->inicio == NULL)
            return 0;
    }

    abate_estoque(car, filial);
    relatorio_pedido(car, id_filial);
    return 1;
}

