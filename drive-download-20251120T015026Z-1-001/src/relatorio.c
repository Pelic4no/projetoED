#include <stdio.h>
#include <stdlib.h>
#include "../include/relatorio.h"

// Relatório do pedido finalizado (exibe no terminal)
void relatorio_pedido(Carrinho *car, int id_filial)
{
    printf("\nPedido finalizado na filial %d\n", id_filial);
    ItemCarrinho *item = car->inicio;

    while(item)
    {
        float subtotal = item->qtd * item->preco;
        printf("Produto %d \n Qtd: %d \n Preço: %.2f \n Subtotal: %.2f\n", item->cod, item->qtd, item->preco, subtotal);
        item = item->prox;
    }

    printf("\nTOTAL: %.2f\n", car->total);
}

// Relatório de diagnóstico por filial (exibe no terminal)
void relatorio_diagnostico(Carrinho *car, DBLojas *db, Catalogo *cat)
{
    Loja *filial = db->inicio;

    while(filial)
    {
        int apta = 1;
        ItemCarrinho *item = car->inicio;

        printf("\nFilial %d \n %s\n", filial->id, filial->nome);

        while(item)
        {
            Estoque *e = filial->estoque;
            int disponivel = 0;

            while(e)
            {
                if(e->cod_prod == item->cod)
                {
                    disponivel = e->qtd;
                    break;
                }
                e = e->prox;
            }

            if(disponivel < item->qtd)
            {
                apta = 0;
                printf("  Faltando: Produto %d \n Qtd faltante: %d\n", item->cod, item->qtd - disponivel);
            }

            item = item->prox;
        }

        if(apta)
            printf("Filial apta para atender 100% do carrinho\n");

        filial = filial->prox;
    }
}

