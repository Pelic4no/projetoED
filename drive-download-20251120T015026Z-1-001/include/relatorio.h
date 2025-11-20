#ifndef RELATORIO_H
#define RELATORIO_H

#include "estruturas.h"

// Gera relatorio do pedido finalizado
void relatorio_pedido(Carrinho *car, int id_filial);

// Gera diagnostico de atendimento por filial
void relatorio_diagnostico(Carrinho *car, DBLojas *db, Catalogo *cat);

#endif
