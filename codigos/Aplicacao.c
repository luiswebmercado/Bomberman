/**
 * Arquivo contendo os métodos referentes a aplicação em si
 * 
 * @author Luís Augusto Weber Mercado
 */

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <time.h>
#include <stdio.h>

#include "../cabecalhos/Aplicacao.h"

void inicializar( Aplicacao *aplicacao )
{
    srand(time(NULL));
    
    if( !al_init() )
    {
        printf("Falha ao iniciar a Allegro.\n");
        aplicacao->contemErros = true;
    }

    if( !al_init_image_addon() )
    {
        printf("Não foi possível carregar o addon de imagens.\n");
        aplicacao->contemErros = true;
    }
    
    if( !al_install_keyboard() )
    {
        printf("Falha ao inicializar a integração com o teclado.\n");
        aplicacao->contemErros = true;
    }
    
    al_init_font_addon();
    al_init_ttf_addon();
   
    criarJanela(aplicacao);
    criarFilaDeEventos(aplicacao);
    criarTimers(aplicacao);

    al_register_event_source(aplicacao->filaEventos, al_get_keyboard_event_source());
    al_register_event_source(aplicacao->filaEventos, al_get_timer_event_source(aplicacao->timerFPS));
    al_register_event_source(aplicacao->filaEventos, al_get_timer_event_source(aplicacao->timerRelogio));
    al_register_event_source(aplicacao->filaEventos, al_get_display_event_source(aplicacao->janela));
    
    // Seta os defaults da aplicação
    aplicacao->modo = MODO_MENU;
    aplicacao->recursos = obterRecursos();
    
    al_start_timer(aplicacao->timerFPS);
    al_start_timer(aplicacao->timerRelogio);
}

void criarJanela( Aplicacao *aplicacao )
{
    aplicacao->janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if( !aplicacao->janela )
    {
        printf("Falha ao criar a janela.\n");
        aplicacao->contemErros = true;
    }

    al_set_window_title(aplicacao->janela, "Bomberman");

    limparConteudoDaJanela();
}

void limparConteudoDaJanela( )
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
}

void criarFilaDeEventos( Aplicacao *aplicacao )
{
    aplicacao->filaEventos = al_create_event_queue();
    if( !aplicacao->filaEventos )
    {
        printf("Falha ao criar fila de eventos.\n");
        aplicacao->contemErros = true;
    }
}

void criarTimers( Aplicacao *aplicacao )
{
    aplicacao->timerFPS = al_create_timer(1.0 / FPS);
    aplicacao->timerRelogio = al_create_timer(1.0);
}

Recursos obterRecursos( )
{
    Recursos recursos;

    recursos.menuTela = al_load_bitmap("./recursos/imagens/menu/tela.png");
    recursos.menuIndicador = al_load_bitmap("./recursos/imagens/menu/indicador.png");
    recursos.menuBombaSprite = al_load_bitmap("./recursos/imagens/menu/Bomba_Sprite.png");
    
    recursos.highscoresTela = al_load_bitmap("./recursos/imagens/highscores/tela.png");
    
    recursos.jogoFundo = al_load_bitmap("./recursos/imagens/jogo/fundo.png");
    recursos.jogoRodape = al_load_bitmap("./recursos/imagens/jogo/rodape.png");
    recursos.jogoObstaculo = al_load_bitmap("./recursos/imagens/jogo/obstaculos/obstaculo.png");
    recursos.jogoObstaculoDestruidoSprite = al_load_bitmap("./recursos/imagens/jogo/obstaculos/obstaculoDestruidoSprite.png");
    recursos.jogoObstaculoFixo = al_load_bitmap("./recursos/imagens/jogo/obstaculos/obstaculoFixo.png");
    recursos.jogoSaida = al_load_bitmap("./recursos/imagens/jogo/portal.png");
    recursos.jogoTelaPausa = al_load_bitmap("./recursos/imagens/jogo/telaPausa.png");
    recursos.jogoTelaGameOver = al_load_bitmap("./recursos/imagens/jogo/telaGameOver.png");
    recursos.jogoTelaVitoria = al_load_bitmap("./recursos/imagens/jogo/telaVitoria.png");
    recursos.jogoBombaSprite = al_load_bitmap("./recursos/imagens/jogo/bomba/Bomba_Sprite.png");
    recursos.jogoRastroSprite = al_load_bitmap("./recursos/imagens/jogo/bomba/Rastro_Sprite.png");
    
    recursos.jogadorFrenteSprite = al_load_bitmap("./recursos/imagens/jogo/bomberman/Bomberman_F_Sprite.png");
    recursos.jogadorFrenteParado = al_load_bitmap("./recursos/imagens/jogo/bomberman/Bomberman_FP.png");
    recursos.jogadorTrasSprite = al_load_bitmap("./recursos/imagens/jogo/bomberman/Bomberman_T_Sprite.png");
    recursos.jogadorTrasParado = al_load_bitmap("./recursos/imagens/jogo/bomberman/Bomberman_TP.png");
    recursos.jogadorLadoSprite = al_load_bitmap("./recursos/imagens/jogo/bomberman/Bomberman_L_Sprite.png");
    recursos.jogadorLadoParado = al_load_bitmap("./recursos/imagens/jogo/bomberman/Bomberman_LP.png");
    recursos.jogadorMortoSprite = al_load_bitmap("./recursos/imagens/jogo/bomberman/Bomberman_M_Sprite.png");
    
    recursos.monstroFrenteSprite = al_load_bitmap("./recursos/imagens/jogo/monstro/Monstro_F_Sprite.png");
    recursos.monstroTrasSprite = al_load_bitmap("./recursos/imagens/jogo/monstro/Monstro_T_Sprite.png");
    recursos.monstroLadoSprite = al_load_bitmap("./recursos/imagens/jogo/monstro/Monstro_L_Sprite.png");
    recursos.monstroMortoSprite = al_load_bitmap("./recursos/imagens/jogo/monstro/Monstro_M_Sprite.png");
        
    recursos.fonteCantarellRegular = al_load_ttf_font("./recursos/fonte/CantarellRegular.ttf", 40, 0);
    recursos.fonteCantarellRegularPequena = al_load_ttf_font("./recursos/fonte/CantarellRegular.ttf", 22, 0);
    recursos.fonteCantarellBold = al_load_ttf_font("./recursos/fonte/CantarellBold.ttf", 40, 0);
    recursos.fonteCantarellBoldPequena = al_load_ttf_font("./recursos/fonte/CantarellBold.ttf", 22, 0);
    
    carregarPontuacoes(recursos.pontuacoes);
    
    return recursos;
}

void carregarPontuacoes(Highscore pontuacoes[])
{
    FILE *arquivo;
    
    if( (arquivo = fopen("./highscores.bin", "r")) != NULL )
    {
        fread(pontuacoes, sizeof(Highscore), MAXIMO_LISTA_HIGHSCORES, arquivo);
        
        fclose(arquivo);
    }
    else
    {
        printf("AVISO: Arquivo de pontuações não encontrado.\n");
        
        int i;
        
        for( i = 0; i < MAXIMO_LISTA_HIGHSCORES; i++ )
        {
            al_ustr_to_buffer(al_ustr_new("Ninguém"), pontuacoes[i].nome, TAMANHO_MAXIMO_NOME);
            pontuacoes[i].pontos = 0;
        }
        
        salvarPontuacoes(pontuacoes);
    }
}

void salvarPontuacoes(Highscore pontuacoes[])
{
    FILE *arquivo;
    
    if( (arquivo = fopen("./highscores.bin", "w")) != NULL )
    {
        fwrite(pontuacoes, sizeof(Highscore), MAXIMO_LISTA_HIGHSCORES, arquivo);
        
        fclose(arquivo);
    }
    else
    {
        printf("AVISO: Arquivo de pontuações não pode ser escrito.\n");
    }
}

void finalizar( Aplicacao* aplicacao )
{
    al_destroy_bitmap(aplicacao->recursos.menuTela);
    al_destroy_bitmap(aplicacao->recursos.menuIndicador);
    al_destroy_bitmap(aplicacao->recursos.menuBombaSprite);
    
    al_destroy_bitmap(aplicacao->recursos.highscoresTela);
    
    al_destroy_bitmap(aplicacao->recursos.jogoFundo);
    al_destroy_bitmap(aplicacao->recursos.jogoRodape);
    al_destroy_bitmap(aplicacao->recursos.jogoObstaculo);
    al_destroy_bitmap(aplicacao->recursos.jogoObstaculoDestruidoSprite);
    al_destroy_bitmap(aplicacao->recursos.jogoObstaculoFixo);
    al_destroy_bitmap(aplicacao->recursos.jogoSaida);
    al_destroy_bitmap(aplicacao->recursos.jogoTelaPausa);
    al_destroy_bitmap(aplicacao->recursos.jogoTelaGameOver);
    al_destroy_bitmap(aplicacao->recursos.jogoTelaVitoria);
    al_destroy_bitmap(aplicacao->recursos.jogoBombaSprite);
    al_destroy_bitmap(aplicacao->recursos.jogoRastroSprite);
    
    al_destroy_bitmap(aplicacao->recursos.jogadorFrenteSprite);
    al_destroy_bitmap(aplicacao->recursos.jogadorFrenteParado);
    al_destroy_bitmap(aplicacao->recursos.jogadorTrasSprite);
    al_destroy_bitmap(aplicacao->recursos.jogadorTrasParado);
    al_destroy_bitmap(aplicacao->recursos.jogadorLadoSprite);
    al_destroy_bitmap(aplicacao->recursos.jogadorLadoParado);
    al_destroy_bitmap(aplicacao->recursos.jogadorMortoSprite);
    
    al_destroy_bitmap(aplicacao->recursos.monstroFrenteSprite);
    al_destroy_bitmap(aplicacao->recursos.monstroTrasSprite);
    al_destroy_bitmap(aplicacao->recursos.monstroLadoSprite);
    al_destroy_bitmap(aplicacao->recursos.monstroMortoSprite);
        
    al_destroy_font(aplicacao->recursos.fonteCantarellRegular);
    al_destroy_font(aplicacao->recursos.fonteCantarellRegularPequena);
    al_destroy_font(aplicacao->recursos.fonteCantarellBold);
    al_destroy_font(aplicacao->recursos.fonteCantarellBoldPequena);
    
    al_destroy_timer(aplicacao->timerFPS);
    al_destroy_timer(aplicacao->timerRelogio);
    al_destroy_event_queue(aplicacao->filaEventos);
    al_destroy_display(aplicacao->janela);
}

ALLEGRO_COLOR obterCorDeFundo( )
{
    return al_map_rgb(19, 20, 38);
}