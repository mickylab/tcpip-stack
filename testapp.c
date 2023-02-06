/*
 * =====================================================================================
 *
 *       Filename:  testapp.c
 *
 *    Description:  This file represents the Test application to test graph topology creation
 *
 * =====================================================================================
 */

#include "graph.h"
#include <stdio.h>
#include "CommandParser/libcli.h"

extern graph_t *build_first_topo();
extern void nw_init_cli();

graph_t *topo = NULL;

int 
main(int argc, char **argv) {
    nw_init_cli();
    topo = build_first_topo();

    start_shell();
    return 0;
}