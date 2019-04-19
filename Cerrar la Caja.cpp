/*
	Name: Cerrar la Caja Version 1.9 (Desde su desarrollo en C) o 2.4 si se toma en cuenta su desarrollo en Pascal
	Copyright: Licencia GNU-GPL 3.0. Para mas informacion visite https://choosealicense.com/licenses/gpl-3.0/#
	Authors: Alejandro Nadal, Bruno Fernandez, Melina Teruel
	Date: 28/10/17 09:18
	Description:Cerrar la caja es un juego diseñado en C, usando las bibliotecas SDL2 y SDL2 Mixer. Para mas informacion sobre estas librerias, visite los
	siguientes enlaces: https://www.libsdl.org/index.php , https://www.libsdl.org/projects/SDL_mixer/
	Las librerias se trasmiten bajo las licencias zlib, lo que nos permite usarlas libremente en cualquier software.
	Ninguno de los tres autores que figuran aqui han participado en el desarrollo de SDL2 y SDL2 Mixer. Para informarse sobre los desarrolladores de 
	estas excelentes bibliotecas graficas/audio, aqui los enlaces.
	https://www.libsdl.org/credits.php
	Autores de SDL Mixer:Sam Lantinga, Stephane Peter, and Ryan Gordon
	
	Este juego ha sido creado para cumplir con los requisitos del Trabajo Práctico Integrados Nª2 de la materia Ingenieria de Sistemas de la Informacion,
	Facultad UTN Regional Resistencia. Profesores: Mirtha Giovannini, Noelia Pinto, Nicolas Tortosa. Si alguien necesita contactarse con los autores, puede 
	escribir a:
	alexandronadal@gmail.com
	meli.a.teruel@gmail.com
	brunofnz28@gmail.com
	Nota: Para que este codigo compile, los siguientes comandos deben estar incluidos en Other Link Options: 
-lmingw32 
-lSDL2main 
-lSDL2 
-lSDL2_mixer
-lSDL2_mixer.dll  

Este codigo va acompañado de las siguientes dll: SDL2.dll SDL2_Mixer.dll, libogg-0.dll,libvorbis-0.dll, libvorbisfile-3.dll
Si usted ha recibido el codigo sin sus respectivas dll, puede descargarlas de los links proporcionados arriba. 
Tambien deberá instalar las librerias en su computadora. Los enlaces tambien estan en los links proporcionados, asi como instrucciones detalladas de instalación
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <time.h>
#define XTEXTO 342
#define YTEXTO 50
SDL_Window *pantalla;
SDL_Surface *creds;
SDL_Surface *credtexts;
SDL_Surface *fondos;
SDL_Surface *iconitos;
SDL_Surface *instrucs;
SDL_Surface *bgs;//Fondo de juego
SDL_Surface *pelotitas;//pelotita que muestra los elementos ocupados de la caja
SDL_Surface *mensajeotrodados;
SDL_Surface *men1a2dados;
SDL_Surface *men1a3dados;
SDL_Surface *ingrese2num;
SDL_Surface *ingrese3num;
SDL_Surface *ingresenum;
SDL_Surface *mensaje1s;//Ingresarnumerodejugadores
SDL_Surface *ganadors;
SDL_Surface *perdedors;
SDL_Surface *numeros;
SDL_Surface *imdado1s;
SDL_Surface *imdado2s;
SDL_Surface *menganadors;
    
SDL_Renderer *ren;
//****Texturas****/
SDL_Texture *numero;
SDL_Texture *fondo;
SDL_Texture *iconito;
SDL_Texture *instruc;
SDL_Texture *bg;//Text Fondo Juego
SDL_Texture *cred;
SDL_Texture *credtext;
SDL_Texture *pelotita;//pelotita que muestra los elementos ocupados de la caja
SDL_Texture *mensaje;
SDL_Texture *ganador;
SDL_Texture *perdedor;
SDL_Texture *imdado1;
SDL_Texture *imdado2;
//****Rects****//
SDL_Rect icredr;
SDL_Rect iconitor;
SDL_Rect mensaje1r;
SDL_Rect mensajer;
SDL_Rect pelotitar;
SDL_Rect numeror;
SDL_Rect destinor;
SDL_Rect imdado1r;
SDL_Rect destino1r;
SDL_Rect imdado2r;
SDL_Rect destino2r;
//****Musica****//
Mix_Chunk *sonpierde;
Mix_Music *musmenu, *musjuego,*muscreditos,*musganar;
int arreglopuntos[9];
int posicionescaja[5]={101,162,228,295,366};
int opc,pos,dado1,dado2,total,numjugadores,completo, puedeseguir,turno;
SDL_Event lecturaflechas,enter,jugadores,cantnumeros;
int caja[9];
void tapafondo(); void imprime_numero(int num, int x, int y);void imprime_dado(int numm1, int numm2);
FILE *F;

//Para numeros usados como bool, 0 es falso y 1 es verdadero
//TODO LIST:
//Modificar la funcion imprime numero para que los numeros puedan ser impresos mas grandes en llas pantallas de ganar y perder
//Implementar la caminata sobre el puente

int x,y,s,loop,cantnum,numdes,num1,num2,num3,k,p;

int devuelvemenor()//Esta funcion devuelve el jugador con puntaje menor
{
	int c,menorpun,menorjug;
	menorpun=100;
	for(c=0;c<numjugadores;c++)
	{
		if(arreglopuntos[c]< menorpun)
		{
			menorpun=arreglopuntos[c];
			menorjug=c;
		}
	}
	menorjug=menorjug+1;
	return menorjug;
}
void humanito_camina()//Hace que el sprite camine sobre el puente
{
	int h,b;
	b=1;
	Mix_PlayMusic(musganar,-1);
	SDL_Surface *humanitos;
    SDL_Texture *humanito;
    SDL_Surface *puentes;
    SDL_Texture *puente;
    SDL_Rect humanitor;
    SDL_Rect destinnor;
    destinnor.y=491;//establecer posicion
    humanitos=SDL_LoadBMP ("Recursos\\humanito.bmp");
    puentes=SDL_LoadBMP ("Recursos\\puente.bmp");
    puente=SDL_CreateTextureFromSurface (ren,puentes);
    SDL_SetColorKey (humanitos,SDL_TRUE,SDL_MapRGB(humanitos->format,255,255,255));
    humanito=SDL_CreateTextureFromSurface (ren,humanitos);
    humanitor.w=150;
    humanitor.h=122;
    destinnor.w=145;
    destinnor.h=122;
    humanitor.y=0;
    for(h=146;h<729;h=h+30)
    {
    	if(b==1)
    	{
        	humanitor.x=130;
        	b=2;
    	}
    	else
    	{
    		if(b==2)
			{
        	humanitor.x=280;
        	b=1;
    		}
        }
	
			destinnor.x=h;
        	SDL_Delay(200);
        	SDL_RenderClear(ren);
			SDL_RenderCopy(ren,puente,NULL,NULL);
        	SDL_RenderCopy(ren,humanito,&humanitor,&destinnor);
        	SDL_RenderPresent(ren);
    	
	}
	SDL_DestroyTexture(humanito);
	SDL_FreeSurface(humanitos);
}
	


void mostrar_ganar()
{
	
    ganador=SDL_CreateTextureFromSurface(ren,ganadors);
    SDL_RenderCopy(ren,ganador,NULL,NULL);
    imprime_numero(turno,700,250);
    SDL_RenderPresent(ren);
    Mix_FadeOutMusic(4500);
    SDL_Delay(5000);
    Mix_PlayMusic(musjuego,-1);
    
}
void vaciamemoria()
{
	SDL_FreeSurface(creds);
	SDL_FreeSurface (fondos);
	SDL_FreeSurface (iconitos);
	SDL_FreeSurface (instrucs);
	SDL_FreeSurface (bgs);
	SDL_FreeSurface (pelotitas);
	SDL_FreeSurface (mensajeotrodados);
	SDL_FreeSurface (men1a2dados);
	SDL_FreeSurface (men1a3dados);
	SDL_FreeSurface (ingrese2num);
	SDL_FreeSurface (ingrese3num);
	SDL_FreeSurface (ingresenum);
	SDL_FreeSurface (mensaje1s);//Ingresarnumerodejugadores
	SDL_FreeSurface (ganadors);
	SDL_FreeSurface (perdedors);
	SDL_FreeSurface (imdado1s);
	SDL_FreeSurface (imdado2s);
	SDL_FreeSurface(menganadors);
	SDL_DestroyTexture (numero);
	SDL_DestroyTexture (fondo);
	SDL_DestroyTexture (bg);//Text Fondo Juego
	SDL_DestroyTexture (iconito);
	SDL_DestroyTexture (instruc);
	SDL_DestroyTexture (cred);
	SDL_DestroyTexture (credtext);//pelotita que muestra los elementos ocupados de la caja
	SDL_DestroyTexture (mensaje);
	SDL_DestroyTexture (ganador);
	SDL_DestroyTexture (perdedor);
	SDL_DestroyTexture (imdado1);
	SDL_DestroyTexture (imdado2);
    
}

void mostrar_perder()
{
    perdedor=SDL_CreateTextureFromSurface(ren,perdedors);
    SDL_RenderCopy(ren,perdedor,NULL,NULL);
    imprime_numero(turno,953,270);
    SDL_RenderPresent(ren);
    Mix_FadeOutMusic(300);
    SDL_Delay(100);
    Mix_PlayChannel(1,sonpierde,0);
    SDL_Delay(4000);
    Mix_FadeInMusic(musjuego,-1,1000);
}

void deter_comp()//Determinamos si el puente esta listo o no.
{
    int c2;
    c2=1; //verdad
    for(k=0;k<=8;k++)//Buscamos celdas vacias. 
    {
        if(caja[k]==0)
        {
            c2=0;
        }
    }
    if (c2==0)//Hay Celdas vacias
    {
        completo=0;
    }
    else//No las hay
    {
        completo=1;
        humanito_camina();
        mostrar_ganar();
    }
}

void puntos()//Contamos los puntos
{
    for(k=0;k<=8;k++)
    {
        if(caja[k]==0)
            p=p+k+1;
    }
    arreglopuntos[turno-1]=p;//Es turno -1 porque los arreglos de C comienzan en 0 pero es poco natural tener un jugador 0
    fprintf(F,"\nJugador %d con puntaje %d\n",turno,arreglopuntos[turno-1]);
    p=0;
}

void carga()//Carga los recursos necesarios
{
	SDL_Surface *logos = SDL_LoadBMP("Recursos\\imagencarga.bmp");
	SDL_Texture *logo =SDL_CreateTextureFromSurface(ren,logos);
	SDL_RenderCopy(ren,logo,NULL,NULL);
	SDL_RenderPresent(ren);
	iconitos=SDL_LoadBMP("Recursos\\icono.bmp");
    fondos= SDL_LoadBMP("Recursos\\Fondo.bmp");
    men1a2dados=SDL_LoadBMP("Recursos\\dado.bmp");
	men1a3dados=SDL_LoadBMP("Recursos\\men1a3num.bmp");
	bgs=SDL_LoadBMP("Recursos\\FONDOJUGAR.bmp");
	mensaje1s=SDL_LoadBMP("Recursos\\mensaje1.bmp");
	mensajeotrodados=SDL_LoadBMP("Recursos\\tirarotrodado.bmp");
	ingrese2num=SDL_LoadBMP("Recursos\\ingrese2numeros.bmp");
	ingrese3num=SDL_LoadBMP("Recursos\\ingrese3numeros.bmp");
	pelotitas=SDL_LoadBMP("Recursos\\table.bmp");
	ganadors=SDL_LoadBMP("Recursos\\ganador.bmp");
	perdedors=SDL_LoadBMP("Recursos\\perdedor.bmp");
	sonpierde=Mix_LoadWAV("Recursos\\Perder.wav");
	numeros=SDL_LoadBMP ("Recursos\\numero.bmp");
	creds= SDL_LoadBMP("Recursos\\creditos.bmp");
    credtexts= SDL_LoadBMP("Recursos\\creditos1.bmp");
    imdado1s=SDL_LoadBMP ("Recursos\\dadoim.bmp");
    imdado2s=SDL_LoadBMP ("Recursos\\dadoim.bmp");
	menganadors=SDL_LoadBMP("Recursos\\mensajeganador.bmp");
	if(sonpierde == NULL)
	{
		fprintf(F,SDL_GetError());
		fprintf(F,"Sonido Perder.wav no cargado");
	}
	Mix_VolumeChunk(sonpierde,100);
	musjuego=Mix_LoadMUS("Recursos\\musicajuego.ogg");
	if(musjuego==NULL)
	{
		fprintf(F,SDL_GetError());
		fprintf(F,"\nNo cargo musjuego\n");
	}
	musganar=Mix_LoadMUS("Recursos\\ganar.ogg");
	muscreditos=Mix_LoadMUS("Recursos\\Creditos.ogg");
	musmenu=Mix_LoadMUS("Recursos\\musicamenu.ogg");
	
}
void alphaset()//Hace que el color blanco de los mensajes sea transparente
{
	SDL_SetColorKey(iconitos,SDL_TRUE,SDL_MapRGB(iconitos->format,255,255,255));
	SDL_SetColorKey(mensajeotrodados,SDL_TRUE,SDL_MapRGB(mensajeotrodados->format,255,255,255));
	SDL_SetColorKey(men1a2dados,SDL_TRUE,SDL_MapRGB(men1a2dados->format,255,255,255));
	SDL_SetColorKey(men1a3dados,SDL_TRUE,SDL_MapRGB(men1a3dados->format,255,255,255));
	SDL_SetColorKey(mensaje1s,SDL_TRUE,SDL_MapRGB(mensaje1s->format,255,255,255));
	SDL_SetColorKey(ingrese2num,SDL_TRUE,SDL_MapRGB(ingrese2num->format,255,255,255));
	SDL_SetColorKey(ingrese3num,SDL_TRUE,SDL_MapRGB(ingrese3num->format,255,255,255));
	SDL_SetColorKey(pelotitas,SDL_TRUE,SDL_MapRGB(pelotitas->format,255,255,255));
	SDL_SetColorKey(menganadors,SDL_TRUE,SDL_MapRGB(menganadors->format,255,255,255));
}
void createxturas()//
{
	pelotita=SDL_CreateTextureFromSurface(ren,pelotitas);
}
void prepararects()
{
	pelotitar.y=346;
	destino1r.x=77;
    destino1r.y=163;
    destino2r.x=306;
    destino2r.y=163;
}

void iniciarcaja()
{
	int z;
	for(z=0;z<=8;z++)
	{
		caja[z]=0;
	}
}
int tecla_numeros(int t)
{
    int j;
    j=0;
    if(t==0)
    {
		
		while(j==0)
	    {
	        while(SDL_PollEvent(&jugadores))//Bucle de eventos
	        {
	            printf("%d",j);
	            if(jugadores.type == SDL_KEYDOWN)
	            {
	                switch (jugadores.key.keysym.sym)
	                {
	                case SDLK_s: j=10;break; //tecla s
	                case SDLK_n: j=11;break; //tecla n
	                }
	            }
	            if(jugadores.type == SDL_MOUSEBUTTONDOWN)
                {
                	switch(jugadores.button.button)
                	{
                		case SDL_BUTTON_LEFT: Mix_VolumeMusic(0);break;
						case SDL_BUTTON_RIGHT: Mix_VolumeMusic(100);break;
					}
					
				}
	        }
	        SDL_Delay(10);
	    }
	}
	if(t==1)
	{
		while(j==0)
	    {
	        while(SDL_PollEvent(&jugadores))//Bucle de eventos
	        {
	            printf("%d",j);
	            if(jugadores.type == SDL_KEYDOWN)
	            {
	                switch (jugadores.key.keysym.sym)
	                {
	                case SDLK_1: j=1;break;
	                case SDLK_2: j=2;break;
	                case SDLK_3: j=3;break;
	                case SDLK_4: j=4;break;
	                case SDLK_5: j=5;break;
	                case SDLK_6: j=6;break;
	                case SDLK_7: j=7;break;
	                case SDLK_8: j=8;break;
	                case SDLK_9: j=9;break;
	                }
	            }
	            if(jugadores.type == SDL_MOUSEBUTTONDOWN)
                {
                	switch(jugadores.button.button)
                	{
                		case SDL_BUTTON_LEFT: Mix_VolumeMusic(0);break;
						case SDL_BUTTON_RIGHT: Mix_VolumeMusic(100);break;
					}
					
				}
	        }
	        SDL_Delay(10);
	    }
	
	}
	if(t==2)
	{
		while(j==0)
	    {
	        while(SDL_PollEvent(&jugadores))//Bucle de eventos
	        {
	            printf("%d",j);
	            if(jugadores.type == SDL_KEYDOWN)
	            {
	                switch (jugadores.key.keysym.sym)
	                {
	                case SDLK_1: j=1;break;
	                case SDLK_2: j=2;break;
	                case SDLK_x: j=121;break;
	                }
	            }
	            if(jugadores.type == SDL_MOUSEBUTTONDOWN)
                {
                	switch(jugadores.button.button)
                	{
                		case SDL_BUTTON_LEFT: Mix_VolumeMusic(0);break;
						case SDL_BUTTON_RIGHT: Mix_VolumeMusic(100);break;
					}
					
				}
	        }
	        SDL_Delay(10);
	    }
			
	}
	if(t==3)
	{
		while(j==0)
	    {
	        while(SDL_PollEvent(&jugadores))//Bucle de eventos
	        {
	            printf("%d",j);
	            if(jugadores.type == SDL_KEYDOWN)
	            {
	                switch (jugadores.key.keysym.sym)
	                {
	                case SDLK_1: j=1;break;
	                case SDLK_2: j=2;break;
	                case SDLK_3: j=3;break;
	                case SDLK_x: j=121;break;
	                }
	            }
	            if(jugadores.type == SDL_MOUSEBUTTONDOWN)
                {
                	switch(jugadores.button.button)
                	{
                		case SDL_BUTTON_LEFT: Mix_VolumeMusic(0);break;
						case SDL_BUTTON_RIGHT: Mix_VolumeMusic(100);break;
					}
					
				}
	        }
	        SDL_Delay(10);
	    }
	}
return j;
}

void imprime_numero(int num, int x, int y)
{
 
    destinor.x=x;
    destinor.y=y;
    
    SDL_SetColorKey (numeros,SDL_TRUE,SDL_MapRGB(numeros->format,255,255,255));
    numero=SDL_CreateTextureFromSurface (ren,numeros);
    switch(num)
    {
        case 1 :numeror.x=0;break;
        case 2 :numeror.x=97;break;
        case 3 :numeror.x=182;break;
        case 4 :numeror.x=289;break;
        case 5 :numeror.x=379;break;
        case 6 :numeror.x=479;break;
        case 7 :numeror.x=572;break;
        case 8 :numeror.x=673;break;
        case 9 :numeror.x=765;break;
        case 10 :numeror.x=871;break;
        case 11 :numeror.x=961;break;
        case 12 :numeror.x=1065;break;
        default :numeror.x=27*(num-1);break; 
	}
    numeror.y=0;
    numeror.w=75;
    numeror.h=52;
    destinor.w=75;
    destinor.h=52;
    SDL_RenderCopy(ren,numero,&numeror,&destinor);


}
void tiradores()
{
	cantnum=0;
	numdes=0;
	dado1=1+rand()%6;
	total=dado1;
	tapafondo();
	SDL_PumpEvents();
	SDL_FlushEvent(SDL_KEYDOWN);
	if((caja[6]==0)||(caja[7]==0)||(caja[8]==0))//El usuario usa dos dados automaticamente
	{
	dado2=1+rand()%6;
	fprintf(F,"El valor del dado2 es de %d",dado2);
	}
	else
	{
		tapafondo();
		mensaje=SDL_CreateTextureFromSurface(ren,mensajeotrodados);
		SDL_QueryTexture(mensaje,NULL,NULL,&mensajer.w,&mensajer.h);
		SDL_RenderCopy(ren,mensaje,NULL,&mensajer);
		SDL_RenderPresent(ren);
		numdes=tecla_numeros(0);
	    if(numdes==10)// 10 es SI,
        {
            dado2=rand()%9; //da un valor aleatorio al dado2
	    }
	    if(numdes==11)
        {
            dado2=0; // si des es NO es 10 da un valor cero
        }
	//Añadir aca la eleccion si o no, y luego de eso sumar o no el dado2 a total. Luego de eso este else no tiene otra funcion
	//Como estamos usando para todos los mensajes la misma textura, aca abra que renderizar el mensaje
	//Aca aun hay que implementar el
	}

	total=dado1+dado2;
	fprintf(F,"El total es %d\n",total);
	tapafondo();
	if(total < 6)
	{
		mensaje=SDL_CreateTextureFromSurface(ren,men1a2dados);
		SDL_QueryTexture(mensaje,NULL,NULL,&mensajer.w,&mensajer.h);
		SDL_RenderCopy(ren,mensaje,NULL,&mensajer);//pasar a render "Uno o 2 numeros
		SDL_RenderPresent(ren);
		fprintf(F,"Total < 6\n");
		cantnum=tecla_numeros(2);
	}
	if(total>=6)
	{
		fprintf(F,"Total > 6\n");
		mensaje=SDL_CreateTextureFromSurface(ren,men1a3dados);
		SDL_QueryTexture(mensaje,NULL,NULL,&mensajer.w,&mensajer.h);
		SDL_RenderCopy(ren,mensaje,NULL,&mensajer);//pasar a render "Uno o 2 o 3 numeros
		SDL_RenderPresent(ren);
		cantnum=tecla_numeros(3);
	}
	if(cantnum==1)
	{
		if(total > 9 || caja[total-1] == 1)
		{
		    mostrar_perder();
			puedeseguir=0;
		}
		else
			{
				caja[total-1]=1;
			}
	}
	if(cantnum==2)
	{
		mensaje=SDL_CreateTextureFromSurface(ren,ingrese2num);
		SDL_QueryTexture(mensaje,NULL,NULL,&mensajer.w,&mensajer.h);
		tapafondo();
		SDL_RenderCopy(ren,mensaje,NULL,&mensajer);
		SDL_RenderPresent(ren);
		num1=tecla_numeros(1);
		imprime_numero(num1,610,277);
		SDL_RenderPresent(ren);
		num2=tecla_numeros(1);
		imprime_numero(num2,650,277);
		SDL_RenderPresent(ren);

        if((num1+num2)==total)
        {
            if((caja[num1-1]==0)&&(caja[num2-1]==0))
            {
                caja[num1-1]=1;
                caja[num2-1]=1;
            }
        	else
        	{
        	    mostrar_perder();
        		puedeseguir=0;
			}
		}
		else
		{
		    mostrar_perder();
			puedeseguir=0;
		}
	}
	if(cantnum==3)
	{
		mensaje=SDL_CreateTextureFromSurface(ren,ingrese3num);
		SDL_QueryTexture(mensaje,NULL,NULL,&mensajer.w,&mensajer.h);
		tapafondo();
		SDL_RenderCopy(ren,mensaje,NULL,&mensajer);
		SDL_RenderPresent(ren);
		num1=tecla_numeros(1);
		imprime_numero(num1,610,277);
		SDL_RenderPresent(ren);
        num2=tecla_numeros(1);
        imprime_numero(num2,670,277);
        SDL_RenderPresent(ren);
        num3=tecla_numeros(1);
        imprime_numero(num3,730,277);
        SDL_RenderPresent(ren);
        if((caja[num1-1]==0)&&(caja[num2-1]==0)&&(caja[num3-1]==0)&&(num1+num2+num3)==total)
        {
            caja[num1-1]=1;
            caja[num2-1]=1;
            caja[num3-1]=1;
        }
        else
        {
            mostrar_perder();
            puedeseguir=0;
        }
		//Ingresar los 3 numeros con la funcion teclanum
		//comprobar que sean correctos
		//llamar a la funcion que muestra el arreglo
	}
	//Y en esto consiste la estructura de tiradores. Cambio del original un poco porque procesamos el caso 789=1 en la parte superior.

	SDL_RenderPresent(ren);
	dado2=0;
	fprintf(F,"DATA DUMP");
	fprintf(F,"Num1: %d, Num2 %d, Num3, %d",num1,num2,num3);
	fprintf(F,"Decision de cantidad de numeros %d",cantnum);

}

void rellenacaja()
{
    for(k=0;k<=8;k++)
    {
        if(caja[k]==1)
            {
                switch(k)
                {
                    case 0: pelotitar.x=240;break;
                    case 1: pelotitar.x=299;break;
                    case 2: pelotitar.x=357;break;
                    case 3: pelotitar.x=417;break;
                    case 4: pelotitar.x=477;break;
                    case 5: pelotitar.x=536;break;
                    case 6: pelotitar.x=596;break;
                    case 7: pelotitar.x=655;break;
                    case 8: pelotitar.x=716;break;
                }
            SDL_QueryTexture(pelotita,NULL,NULL,&pelotitar.w,&pelotitar.h);
            SDL_RenderCopy(ren,pelotita,NULL,&pelotitar);
            }
    }
	SDL_RenderPresent(ren);
}
void tapafondo()
{
	SDL_RenderCopy(ren,bg,NULL,NULL);
	imprime_numero(turno,246,8);
	imprime_numero(total,218,86);
	imprime_dado(dado1,dado2);
	rellenacaja();
	SDL_RenderPresent(ren);
}
void creditos()//Imprime los creditos
{
    Mix_PlayMusic(muscreditos,-1);
	int i;
    if(creds == NULL)
    {
        printf("No se encontro el objeto");
        printf(SDL_GetError());
    }
    cred=SDL_CreateTextureFromSurface(ren,creds);
    SDL_SetColorKey(credtexts,SDL_TRUE,SDL_MapRGB(credtexts->format,255,255,255));
    credtext=SDL_CreateTextureFromSurface(ren,credtexts);
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren,cred,NULL,NULL);
    x=250;
    icredr.x=x;
     SDL_QueryTexture(credtext,NULL,NULL,&icredr.w,&icredr.h);
    for(i=713;i>0;i=i-5)//Van subiendo
    {
        icredr.y=i;
        SDL_Delay(15);
       
        SDL_RenderCopy(ren,cred,NULL,NULL);
        SDL_RenderCopy(ren,credtext,NULL,&icredr);
        SDL_RenderPresent(ren);
    }
    Mix_FadeOutMusic(1000);
}
void imprime_dado(int numm1, int numm2)//Practicamente un scanf con validacion automatica. 
{
    imdado1=SDL_CreateTextureFromSurface (ren,imdado1s);
    imdado2=SDL_CreateTextureFromSurface (ren,imdado2s);
    switch(numm1)
    {
        case 1 :imdado1r.x=308;break;
        case 2 :imdado1r.x=462;break;
        case 3 :imdado1r.x=770;break;
        case 4 :imdado1r.x=616;break;
        case 5 :imdado1r.x=154;break;
        case 6 :imdado1r.x=0;break;
        default :imdado1r.x=27*(numm1-1);break;
	}
    switch(numm2)
    {
        case 1 :imdado2r.x=308;break;
        case 2 :imdado2r.x=462;break;
        case 3 :imdado2r.x=770;break;
        case 4 :imdado2r.x=616;break;
        case 5 :imdado2r.x=154;break;
        case 6 :imdado2r.x=0;break;
        default :imdado2r.x=27*(numm1-1);break;
    }
    imdado1r.y=0;
    imdado1r.w=155;
    imdado1r.h=156;
    imdado2r.y=0;
    imdado2r.w=155;
    imdado2r.h=156;
    destino1r.w=155;
    destino1r.h=156;
    destino2r.w=155;
    destino2r.h=156;
    SDL_RenderCopy(ren,imdado1,&imdado1r,&destino1r);
    if(dado2!=0)
	SDL_RenderCopy(ren,imdado2,&imdado2r,&destino2r);
}
void instrucciones()
{
    int status;
    status=1;
	while(status <3)
	{

		if(status == 1)
		fondos= SDL_LoadBMP("Recursos\\instrucciones.bmp");
		else
		fondos=SDL_LoadBMP("Recursos\\instrucciones2.bmp");

	    if(fondos == NULL)
	    {
	        printf("No se encontro el objeto");
	        printf(SDL_GetError());
	    }
	    fondo=SDL_CreateTextureFromSurface(ren,fondos);//Crear Textura
	    SDL_RenderClear(ren);
	    SDL_RenderCopy(ren,fondo,NULL,NULL);
	    SDL_RenderPresent(ren);
	    while(SDL_PollEvent(&enter))
	    {
	    	if(enter.type==SDL_KEYDOWN)
	    	status=status+1;
	    	SDL_Delay(40);
		}
		SDL_Delay(50);
		SDL_FreeSurface(fondos);//Como estamos cargando los bmp dentro de un bucle es importante vaciar la memoria que ocupa
		SDL_DestroyTexture(fondo);//Si alguien desea colgar su computadora, retire estas lineas y entre a instrucciones. No recomendado.
	}
	fondos= SDL_LoadBMP("Recursos\\Fondo.bmp"); //Volvemos a imprimir la pantalla de menu
	fondo=SDL_CreateTextureFromSurface(ren,fondos);
	SDL_RenderCopy(ren,fondo,NULL,NULL);
}

void jugar()
{
    //Inicializar variables
    fprintf(F, "Hemos ingresado a jugar");
    Mix_FadeInMusic(musjuego,-1,1000);
    loop=1;
    numjugadores=0;
    turno=1;
   	bg=SDL_CreateTextureFromSurface(ren,bgs);
	mensajer.x=XTEXTO;
	mensajer.y=YTEXTO;
   	mensaje=SDL_CreateTextureFromSurface(ren,mensaje1s);
    fprintf(F,"\n ingresamos al main loop");

    while((loop > 0)&&(loop < 4))//Bucle principal de juego. Trabaja con un rango para cambiar de estado dentro del mismo usando la misma variable
    {
		if(loop == 1)//Carga de Datos
        {
        SDL_RenderCopy(ren,bg,NULL,NULL);//Copia al render del fondo
        SDL_QueryTexture(mensaje,NULL,NULL,&mensajer.w,&mensajer.h);//Imprimir el mensaje al usuario
        SDL_RenderCopy(ren,mensaje,NULL,&mensajer);//Copiar al render el mensaje al usuario
        SDL_RenderPresent(ren);//Renderizar
        numjugadores=tecla_numeros(1);
        loop=2;
        }
        if(loop == 2)
        {
            printf("Llegamos a loop2");
            while(turno <= numjugadores)
            {
            	iniciarcaja();
            	while((completo==0)&&(puedeseguir==1))
        	    {
				tiradores();
				rellenacaja();
				tapafondo();
				deter_comp();
				}
				
                puntos();
				turno=turno+1;
                puedeseguir=1;
                completo=0;
                printf("\nEl turno %d termino",turno);
			}
			mensaje=SDL_CreateTextureFromSurface(ren,menganadors);
			fprintf(F,"\n%d\n",devuelvemenor());
			SDL_RenderClear(ren);
			imprime_numero(devuelvemenor(),730,191);
			SDL_RenderCopy(ren,mensaje,NULL,&mensajer);
			SDL_RenderPresent(ren);
			SDL_Delay(2000);
			loop=5;
			fclose(F);
		}
    }
    Mix_FadeOutChannel(1,800);
}


void menu()
{
    //Inicializando variables
	pos=0;
    x=285;
    s=1;
    iconitor.x=x;
    opc=5;
    completo=0;
    puedeseguir=1;
	//Mix_VolumeChunk(musmenu,100);
	
    srand(time(NULL));//semilla aleatoria
    //Comprobando ubicaciones
    if(fondos == NULL)
    {
        printf("No se encontro el objeto");
        printf(SDL_GetError());
    }
    if (iconitos == NULL)
    {
    	printf("No se encontro el objeto icono");
    	printf(SDL_GetError());
	}

	//Canales Alfa

    //Creando Texturas
    fondo=SDL_CreateTextureFromSurface(ren,fondos);
	iconito=SDL_CreateTextureFromSurface(ren,iconitos);

    SDL_RenderClear(ren);//Limpiando Renders
    SDL_RenderCopy(ren,fondo,NULL,NULL);
	iniciarcaja();
	Mix_PlayMusic(musmenu,-1);
	Mix_VolumeMusic(80);
    while(s==1)//Bucle de Menu
        {
			while(SDL_PollEvent(&lecturaflechas))//Bucle de eventos
            {
                if(lecturaflechas.type == SDL_KEYDOWN)//Tecla presionada
                {
                        if(lecturaflechas.key.keysym.sym==SDLK_DOWN)//Abajo
                        {
                            if(pos==4)
                            {
                                pos=0;
                            }
                            else
                            {
                                pos=pos+1;
                            }
                        }


                        if(lecturaflechas.key.keysym.sym==SDLK_UP)//Arriba
                        {
                            if(pos==0)
                            {
                                pos=4;
                            }
                            else
                            {
                                pos=pos-1;
                            }
                        }
                        if(lecturaflechas.key.keysym.sym==SDLK_ESCAPE)//Salir
                        {
                           s=0;
                        }
                        if(lecturaflechas.key.keysym.sym==SDLK_RETURN)
                        {
                           opc=pos;
                        }
                }
                if(lecturaflechas.type == SDL_MOUSEBUTTONDOWN)
                {
                	switch(lecturaflechas.button.button)
                	{
                		case SDL_BUTTON_LEFT: Mix_VolumeMusic(0);break;
						case SDL_BUTTON_RIGHT: Mix_VolumeMusic(100);break;
					}
					
				}
            }
            y=posicionescaja[pos];//posicion en Y de la cajita
            iconitor.y=y;
            SDL_QueryTexture(iconito,NULL,NULL,&iconitor.w,&iconitor.h);
            SDL_RenderCopy(ren,fondo,NULL,NULL);
            SDL_RenderCopy(ren,iconito,NULL,&iconitor);
            SDL_RenderPresent(ren);
            if(opc != 5)//Si seleccionamos una opcion, la musica de menu se apaga
            {
            	Mix_FadeOutMusic(1000);
			}
            switch(opc)//Entramos a las subacciones
            {
                case 0: printf("JUGAR\n");opc=5;jugar();break;
                case 1: printf("INSTRUCCIONES\n");opc=5;instrucciones();break;
                case 2: printf("CREDITOS\n");opc=5;creditos();break;
                case 3: printf("HALL DE FAMA\n");opc=5;break;
                case 4: printf("SALIR\n");opc=5;s=0;break;
            }
            
        }
}

int main(int argc, char *argv[])//Estos argumentos son necesarios para que SDL funcione. 
{

    F=fopen("Recursos\\Errores.txt","w");
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);//Inicializar SDL
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,4096);//Iniciar audio, dando 4096 bytes a los sonidos cortos
    pantalla= SDL_CreateWindow("Cerrar la Caja", 10, 10, 1024, 768, SDL_WINDOW_SHOWN);//Crear Pantalla
    ren =SDL_CreateRenderer(pantalla,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);//Crear Renderer
    carga();//Cargar Datos
    alphaset();//Trasparentar Blancos
    createxturas();//Establece algunas texturas
    prepararects();
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);//El limpiador de render funcionara en blanco
    Mix_AllocateChannels(2);
    int volume=70;
    Mix_VolumeMusic(volume);
    menu();
    SDL_DestroyWindow(pantalla); // Cierra la ventana
    vaciamemoria();//Destruimos todo lo creado en memoria 
    Mix_CloseAudio();//Cerramos el subsistema de audio
	SDL_Quit();

    return 0;
}


