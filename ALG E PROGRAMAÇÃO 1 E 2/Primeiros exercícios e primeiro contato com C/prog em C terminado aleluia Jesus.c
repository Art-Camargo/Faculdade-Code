#include <stdio.h>
int escolha_menu()
{
    int opcao;
    printf("\n1 - cadastrar metal");
    printf("\n2 - remover metal");
    printf("\n3 - quantidades de chapas de metal estocadas por tipo");
    printf("\n4 - tipos de chapas de metal sem estoque");
    printf("\n5 - quantidade total de chapas de metal estocadas");
    printf("\n6 - quantidade em metros quadrados estocados");
    printf("\n7 - alteracao da quantidade de chapas estocadas");
    printf("\n8 - FIM");
    printf("\nDIGITE UMA OPCAO: ");
    scanf("%d", &opcao);
    while(opcao>8 || opcao < 1)
    {
        printf("\nEscolha uma opcao valida do Menu: ");
        scanf("%d", &opcao);
    }
    return opcao;
}
main()
{
    int op, qtd_metal[5], tipo_cada_metal[5], aux=0, tipo_user, i, qtd_soma[3];
    int somatotal, verifica_tipos[3], codigo, adc, armazena_soma_sub;
    float soma_metros_quad=0;
    //aqui zera o contador de tipos:
    for(i=0; i<3; i++){
        qtd_soma[i]=0;
        verifica_tipos[i]=0;
    }
    for(i=0; i<5; i++){
        qtd_metal[i]=0;
        tipo_cada_metal[i]=0;
    }
    while(op!=8){   //aqui chama a funcao:
        op=escolha_menu();
        if(op==8){
            printf("\n\n ******Programa Finalizado******");
        }
        else{   // aqui faz os casos do programa:
            switch(op)
            {   //case do cadastro e metais:
                case 1: // for que valida se ha espaco p armazenar metal e da em ordem crescente de codigo;
                        if(tipo_cada_metal[0]!=0 && tipo_cada_metal[1]!=0 && tipo_cada_metal[2]!=0 && tipo_cada_metal[3]!=0 && tipo_cada_metal[4]!=0)
                        {
                            aux=5;
                        }
                        else
                        {
                            for(i=4; i>=0; i--)
                            {
                                if(tipo_cada_metal[i]==0)
                                {
                                    aux=i;
                                }
                            }
                        }
                        if(aux<5)
                        {
                            printf("\nInforme o tipo do metal %d:  ", aux);
                            scanf("%d", &tipo_cada_metal[aux]);
                            while(tipo_cada_metal[aux]>3 || tipo_cada_metal[aux]<1)
                            {
                                printf("\nInforme um valor valido para o tipo do metal %d: ", aux);
                                scanf("%d", &tipo_cada_metal[aux]);
                            }
                            printf("\nInforme a quantidade que vc quer armazenar no metal %d tipo %d: ", aux, tipo_cada_metal[aux]);
                            scanf("%d", &qtd_metal[aux]);
                            while(qtd_metal[aux]<0)
                            {
                                printf("\nInforme uma quantidade valida que vc quer armazenar no metal %d tipo %d: ", aux, tipo_cada_metal[aux]);
                                scanf("%d", &qtd_metal[aux]);
                            }
                            //aqui faz a soma de quantos metais por tipo:
                            if(tipo_cada_metal[aux]==1)
                            {
                                qtd_soma[0]=qtd_soma[0] + qtd_metal[aux];
                            }
                            else
                            {
                                if(tipo_cada_metal[aux]==2)
                                {
                                    qtd_soma[1] = qtd_soma[1] + qtd_metal[aux];
                                   
                                }
                                else
                                {
                                    if(tipo_cada_metal[aux]==3)
                                    {
                                        qtd_soma[2] = qtd_soma[2] + qtd_metal[aux];
                                       
                                    }
                                }
                            }
                        }
                        //se ja houver os 5 metais cadastrados, ele informa na tela do usuario:
                        else
                        {
                            printf("\n \n Todos os metais ja estao cadastrados\n \n");
                        }
                        //aqui printa a quantidade e o tipo de cada codigo
                        for(i=0; i<5; i++)
                        {
                           
                            printf("\n codigo == %d   tipo == %d    quantidade == %d", i, tipo_cada_metal[i], qtd_metal[i]);
                        }
                        aux++; //aqui faz um contador pra controle geral do programa:
                break;
                //aqui exclui metal escolhido por c?digo.
                case 2: printf("\nInforme o codigo do metal que deseja remover: ");
                        scanf("%d", &codigo);
                        while(codigo > 4 || codigo < 0)
                        {
                            printf("\nInforme o codigo valido do metal que deseja remover: ");
                            scanf("%d", &codigo);
                        }
                        if(tipo_cada_metal[codigo]==0 || aux==0)
                        {
                            printf("\nCodigo de metal nao cadastrado.");
                        }
                        else
                        {
                            qtd_metal[codigo]=0;
                            tipo_cada_metal[codigo]=0;
                            for(i=0; i<5; i++)
                            {
                                if(tipo_cada_metal!=0)
                                {
                                    printf("\n codigo  %d  tipo  %d  quanidade  %d  ", i, tipo_cada_metal[i], qtd_metal[i]);
                                }
                                else
                                {
                                    printf("\n codigo %d NAO POSSUI CADASTRO", i);
                                }
                            }
                        }
                break;
                //case pra informar quantidade de chapas por tipo :);
                case 3: printf("\nInforme o tipo de chapa de metal: ");
                        scanf("%d", &tipo_user);
                        while(tipo_user>3 || tipo_user < 1)
                        {
                            printf("\nInforme o tipo de chapa de metal valido: ");
                            scanf("%d", &tipo_user);
                        }
                        if(qtd_soma[tipo_user-1]==0)
                        {
                            printf("\nNao possui chapas nesse tipo");
                        }
                        else
                        {
                            printf("\nTOTAL DE chapas DO tipo %d ======= %d", tipo_user, qtd_soma[tipo_user-1]);
                        }
                break;
                //case para informar tipos sem estoque;
                case 4: for(i=0; i<5; i++)
                        {
                            if(tipo_cada_metal[i]==3)
                            {
                                verifica_tipos[2]++;
                            }
                            else
                            {
                                if(tipo_cada_metal[i]==2)
                                {
                                    verifica_tipos[1]++;
                                }
                                else
                                {
                                    if(tipo_cada_metal[i]==1)
                                    {
                                        verifica_tipos[0]++;
                                    }
                                }
                            }
                        }
                        for(i=0; i<3; i++)
                        {
                            if(verifica_tipos[i]<1)
                            {
                                printf("\nO tipo %d nao possui estoque.", i+1);
                            }
                        }
                break;
                //aqui faz a soma total das chapas;
                case 5: somatotal=0;
						for(i=0; i<5; i++)
                        {
                            somatotal=somatotal+qtd_metal[i];
                        }
                        printf("\n quantidade total de chapas de metal estocadas ====== %d\n \n", somatotal);
                break;
                //aqui controla a quantidade de metros quadrados total.
                case 6: soma_metros_quad=0;
                        for(i=0; i<5; i++)
                        {
                           
                            if(tipo_cada_metal[i]==1)
                            {
                                soma_metros_quad= soma_metros_quad + (float)qtd_metal[i]*3.0*1.4;
                            }
                            else
                            {
                                if(tipo_cada_metal[i]==2)
                                {
                                    soma_metros_quad=soma_metros_quad + (float)qtd_metal[i]*2;
                                }
                                else
                                {
                                    if(tipo_cada_metal[i]==3)
                                    {
                                        soma_metros_quad=soma_metros_quad + (float)qtd_metal[i]*3;
                                    }
                                }
                            }
                        }
                        printf("\n\nA quantidade total de metros quadrados ==== %.2f, com duas cadas apos a virgula", soma_metros_quad);
                break;
                case 7: printf("\nInforme o codigo do metal que deseja remover ou adicionar:  ");
                        scanf("%d", &codigo);
                        while(codigo>4 || codigo<0)
                        {
                            printf("\nInforme o codigo do metal que deseja remover ou adicionar, mas de forma valida:  ");
                            scanf("%d", &codigo);
                        }
                        if(tipo_cada_metal[codigo]==0)
                        {
                            printf("\nMetal nao cadastrado.\n\n");
                        }
                        else
                        {
                            printf("\n\nvoce deseja subtrair ou adicionar no metal de codigo %d", codigo);
                            printf("\n1 - REMOVER");
                            printf("\n2 - ADICIONAR");
                            scanf("%d", &adc);
                            while(adc>2 || adc<1)
                            {
                                printf("\nESCOLHA UMA OPCAO VALIDA: ");
                                scanf("%d", &adc);
                            }
                            if(adc==1)
                            {
                                if(qtd_metal[codigo]==0)
                                {
                                    printf("\n nao ha quantidade pra remover desse metal");
                                }
                                else
                                {
                                    printf("\nquanto vc deseja remover do metal %d? ", codigo);
                                    scanf("%d", &armazena_soma_sub);
                                    while(armazena_soma_sub>qtd_metal[codigo])
                                    {
                                        printf("\nNao e possivel remover essa quantidade. Quanto vc deseja remover do metal %d? ", codigo);
                                        scanf("%d", &armazena_soma_sub);
                                    }
                                    qtd_metal[codigo]=qtd_metal[codigo]-armazena_soma_sub;
                                    printf("\nA nova quantidade do metal %d ==== %d", codigo, qtd_metal[codigo]);
                                }
                            }
                            else
                            {
                                printf("\nQuanto vc quer somar na quantidade do metal %d? ", codigo);
                                scanf("%d", &armazena_soma_sub);
                                while(armazena_soma_sub<0)
                                {
                                    printf("\nDe uma opcao valida para: Quanto vc quer somar na quantidade do metal %d? ", codigo);
                                    scanf("%d", &armazena_soma_sub);
                                }
                                qtd_metal[codigo]=qtd_metal[codigo] + armazena_soma_sub;
                                printf("\n\nA nova quantidade do metal %d === %d ", codigo, qtd_metal[codigo]);
                            }
                        }
                break;
            }
        }
    }
}

 
 
 
 
 
 
 
 


