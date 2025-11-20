#ifndef FINALIZA_H
#define FINALIZA_H

#include "estruturas.h"

// Função principal de finalização da compra
// Recebe o carrinho, base de dados, catálogo e ID da filial escolhida
// Retorna 1 se a venda foi finalizada, 0 se foi cancelada
int finaliza(Carrinho *car, DBLojas *db, Catalogo *cat, int id_filial);

// Ajusta o carrinho automaticamente com base no estoque da filial
// Remove itens com quantidade zerada e atualiza o total
void ajusta_carrinho(Carrinho *car, Loja *filial);

// Abate o estoque da filial com os itens do carrinho
void abate_estoque(Carrinho *car, Loja *filial);

// Gera relatório do pedido finalizado
void relatorio_pedido(Carrinho *car, int id_filial);

// Gera diagnóstico de atendimento por filial
void relatorio_diagnostico(Carrinho *car, DBLojas *db, Catalogo *cat);

#endif
