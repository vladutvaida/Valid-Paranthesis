#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
/* Vaida Vlad Marian 315CB */

typedef struct
{
  int id_paranteza;
  char tip;
} INF;

typedef struct celula
{
  void *data;
  struct celula *urm;
} TCelula, *TLG, **ALG;
typedef struct
{
  size_t dim;
  TLG ic;
  TLG sc;
} Coada, *TCoada;
typedef struct
{
  size_t dim;
  TLG vf;
} Stiva, *TStiva;
//Functia care initializeaza stive
void InitS (Stiva * s, size_t dim)
{
  	s->dim = dim;
  	s->vf = NULL;
}
//Functia de push
int push (Stiva * s, void * data)
{  	
	TLG a;
	a = (TCelula *) malloc (sizeof (TCelula));
  	a->data = malloc (s->dim);
  	 memcpy (a->data, data,s->dim);
        a->urm = s->vf;
        s->vf = a;
	
        return 0;
}
//Functia de pop
int pop (Stiva * s)
{
  	TLG a = s->vf;
  	if (!s->vf)
   	return -1;
  	else
   	s->vf = s->vf->urm;
    	free(a->data);
    	free(a);
  	return 0;
}
//Functia de initiaizare de cozi
void InitQ (Coada * q, size_t dim)
{
  	q->dim = dim;
  	q->ic = q->sc = NULL;
}
//Functia care returneaza numarul de elemente din cozi
int elementc (Coada * c)
{
  	int nr = 0;
  	TLG a = c->ic;
  	while (a)
    	{
      	a = a->urm;
      	nr++;
    	}
  	return nr;
}
//Functia care introduce in coada
int intrq (Coada * q, void * data)
{
  	TLG a;
  	a = (TCelula *) malloc (sizeof (TCelula));
  	a->data = malloc (q->dim);
  	if (a == NULL)
    	return -1;
  	a->urm = NULL;
  	memcpy (a->data, data, q->dim);
  	if (!q->ic)
   	 	q->ic = q->sc = a;
  	else
    	{
      		q->sc->urm = a;
      		q->sc = a;
    	}
  	return 0;
}
//Functia care extrage din coada
void extrq (Coada * q)
{
  	TLG a = q->ic;
  
  	if (q->ic)
   	{
      		if (elementc (q) == 1)
		q->ic = q->sc = NULL;
      		else
		q->ic = q->ic->urm;
      		free (a->data);
      		free (a);
        }
}
//Functia care returneaza paranteza din varful stivei
char top (Stiva * s)
{
  if (!s->vf)
    return -1;
  TLG a = s->vf;
  INF y = *(INF *) (a->data);
  return y.tip;
}
//Functia care returneaza id-ul din varful stivei
int Top (Stiva * s)
{
  if (!s->vf)
    return -1;
  TLG a = s->vf;
  INF y = *(INF *) (a->data);
  return y.id_paranteza;
}
//Functia care returneaza paranteza din inceputul cozii
int front (Coada * c)
{
  if (!c->ic)
    return -1;
  else
    {
      TLG a = c->ic;
      INF y = *(INF *) (a->data);
      return y.tip;
    }
}
//Functia care returneaza id-ul din sfarsitul cozii
int Front (Coada * c)
{
  if (!c->ic)
    return -1;
  else
    {
      TLG a = c->ic;
      INF y = *(INF *) (a->data);
      return y.id_paranteza;
    }
}
//Functia care afiseaza coada
void printq (Coada * c,FILE *g)
{
  Coada *C;
  C = malloc (sizeof (Coada));
  InitQ (C, sizeof (INF));
  C->dim = sizeof (INF);
  fprintf (g,"\"");
  while (c->ic)
    {
      TLG a = c->ic;
      INF y = *(INF *) (a->data);
      intrq (C, &y);
      extrq (c);
    }
  
  while (C->ic)
    {
      TLG d = C->ic;
      INF x = *(INF *) (d->data);
      fprintf (g,"%c", front (C));
      intrq (c, &x);
      extrq (C);
    }
   free(C);
   fprintf (g,"\"\n");
}
//Functia care afiseaza stiva
void prints (Stiva * s,FILE *g)
{
  Stiva *S;
  S = malloc (sizeof (Stiva));
  InitS (S, sizeof (INF));
  S->dim = sizeof (INF);
  fprintf (g,"\"");
  while (s->vf)
    {
      TLG a = s->vf;
      INF y = *(INF *) (a->data);
      push (S, &y);
      pop (s);
    }
    
  while (S->vf)
    {
      TLG a = S->vf;
      INF y = *(INF *) (a->data);
      fprintf (g,"%c", top (S));
      push (s, &y);
      pop (S);
    }
   fprintf (g,"\"\n");
   free(S);
}
//Functia care returneaza numarul de elemente din stiva

int elements (Stiva * s)
{
  int nr = 0;

  TLG a = s->vf;
  while (a)
    {
      a = a->urm;
      nr++;
    }
  return nr;

}
//Functia care elibereaza stiva
void eliberares(Stiva *s)
{
 	while(s->vf)
	{
		pop(s);
	}
}	
//Functia care elibereaza coada
void eliberareq(Coada *c)
{
	while(c->ic)
	{
		extrq(c);
	}
}
//Functia care sorteaza stiva
void sorts (Stiva * s)
{
  int nr = 0;
  Stiva *S, *S1;
  S = malloc (sizeof (Stiva));
  InitS (S, sizeof (INF));
  S->dim = sizeof (INF);
  S1 = malloc (sizeof (Stiva));
  InitS (S1, sizeof (INF));
  S1->dim = sizeof (INF);
  int x = elements (s);
  while (nr < x)
    {
      TLG a = s->vf;
      INF y = *(INF *) (a->data);
      push (S, &y);
      pop (s);
      nr++;
      while (s->vf)
	{

	  TLG b = s->vf;
	  TLG c = S->vf;
	  INF z = *(INF *) (b->data);
	  INF f = *(INF *) (c->data);
	  if (Top (s) > Top (S))
	    {
	      push (S1, &f);
	      pop (S);
	      pop (s);
	      push (S, &z);
	    }
	  else
	    {
	      push (S1, &z);
	      pop (s);
	    }

	}

      while (S1->vf)
	{
	  TLG b = S1->vf;
	  INF c = *(INF *) (b->data);
	  push (s, &c);
	  pop (S1);
	}

    }

  while (S->vf)
    {
      TLG a = S->vf;
      INF y = *(INF *) (a->data);
      push (s, &y);
      pop (S);
    }
   free(S);
   free(S1);


}
//Functia care sorteaza coada
void sortq (Coada * c)
{
  int nr = 0;
  Stiva *S, *S1;
  S = malloc (sizeof (Stiva));
  InitS (S, sizeof (INF));
  S->dim = sizeof (INF);
  S1 = malloc (sizeof (Stiva));
  InitS (S1, sizeof (INF));
  S1->dim = sizeof (INF);
  int x = elementc (c);
  while (nr < x)
    {
      TLG a = c->ic;
      INF y = *(INF *) (a->data);
      push (S, &y);
      extrq (c);
      nr++;
      while (c->ic)
	{
	  TLG b = c->ic;
	  TLG d = S->vf;
	  INF z = *(INF *) (b->data);
	  INF f = *(INF *) (d->data);
	  if (Front (c) > Top (S))
	    {
	      push (S1, &f);
	      pop (S);
	      extrq (c);
	      push (S, &z);
	    }
	  else
	    {
	      push (S1, &z);
	      extrq (c);
	    }

	}

      while (S1->vf)
	{
	  TLG b = S1->vf;
	  INF d = *(INF *) (b->data);
	  intrq (c, &d);
	  pop (S1);
	}

    }

  while (S->vf)
    {
      TLG a = S->vf;
      INF y = *(INF *) (a->data);
      intrq (c, &y);
      pop (S);
    }
    free(S);   
    free(S1);


}
//Functia care returneaza numarul maxim de parantezari corecte la stive
int corrects(Stiva *s)
{
	int i = -1,res = 0;
	Stiva *S,*S1,*S2,*S3;
	S = malloc (sizeof (Stiva));
  	InitS (S, sizeof (INF));
  	S->dim = sizeof (INF);
  	S1 = malloc (sizeof (Stiva));
  	InitS (S1, sizeof (INF));
  	S1->dim = sizeof (INF);
	S2 = malloc (sizeof (Stiva));
  	InitS (S2, sizeof (int));
  	S2->dim = sizeof (int);
	S3 = malloc (sizeof (Stiva));
  	InitS (S3, sizeof (INF));
  	S3->dim = sizeof (INF);
	while(s->vf)
	{
		TLG a =s->vf;
		INF y =*(INF *)(a->data);
		push(S,&y);
		push(S1,&y);
		pop(s);
	}
	push(S2,&i);
	while(S->vf)
	{
		TLG a =S->vf;
		INF y=*(INF *)(a->data);
		push(s,&y);
		pop(S);
	}
	
	while(S1->vf)
	{
		TLG a =S1->vf;
		INF y =*(INF *)(a->data);
		i = i + 1;
		if(top(S1)=='{' || top(S1) =='[' || top(S1) =='(')
		{
		push(S2,&i);
		push(S3,&y);
		}
		else if(top(S1) == '}' && top(S3) =='{')
		{	pop(S2); 
			pop(S3);
			
		}
		else if(top(S1) == ']' && top(S3) =='[')
		{	pop(S2);
			pop(S3);
		}
		else if(top(S1) == ')' && top(S3) =='(')
		{	pop(S2);		
			pop(S3);
		}
		else 
		{	push(S2,&i);
			push(S3,&y);
		}
		if(S2->vf)
		{
			TLG b =S2->vf;
			int x =	*(int *)(b->data);
			if(res < i -x)
			res = i - x;
		}
		else
		push(S3,&y);
		pop(S1);
	}
	eliberares(S);
	eliberares(S1);
	eliberares(S2);
	eliberares(S3);
	free(S);
	free(S1);
	free(S2);
	free(S3);	
	return res;	
	
}		
//Functia care returneaza numarul maxim de parantezari corecte la cozi		
int correctq(Coada *c)
{		
	
	int i = -1,res = 0;
	Coada *C;
	Stiva *S1,*S2,*S3,*S;
	C = malloc (sizeof (Coada));
  	InitQ(C, sizeof (INF));
  	C->dim = sizeof (INF);
	S = malloc (sizeof (Stiva));
  	InitS (S, sizeof (INF));
  	S->dim = sizeof (INF);
	S1 = malloc (sizeof (Stiva));
  	InitS (S1, sizeof (INF));
  	S1->dim = sizeof (INF);
	S2 = malloc (sizeof (Stiva));
  	InitS (S2, sizeof (int));
  	S2->dim = sizeof (int);
	S3 = malloc (sizeof (Stiva));
  	InitS (S3, sizeof (INF));
  	S3->dim = sizeof (INF);
	while(c->ic)
	{
		TLG a =c->ic;
		INF y =*(INF *)(a->data);
		intrq(C,&y);
		push(S,&y);
		extrq(c);
	}
	while(C->ic)
	{
		TLG a =C->ic;
		INF y=*(INF *)(a->data);
		intrq(c,&y);
		extrq(C);
	}
	while(S->vf)
	{
		TLG a =S->vf;
		INF y = *(INF *)(a->data);
		push(S1,&y);
		pop(S);
	}
	push(S2,&i);
	while(S1->vf)
	{
		TLG a =S1->vf;
		INF y =*(INF *)(a->data);
		i = i + 1;
		if(top(S1)=='{' || top(S1) =='[' || top(S1) =='(')
		{
		push(S2,&i);
		push(S3,&y);
		}
		else if(top(S1) == '}' && top(S3) =='{')
		{	pop(S2); 
			pop(S3);
		}
		else if(top(S1) == ']' && top(S3) =='[')
		{	pop(S2);
			pop(S3);
		}
		else if(top(S1) == ')' && top(S3) =='(')
		{	pop(S2);		
			pop(S3);
		}
		else
		{	push(S2,&i);
			push(S3,&y);
		}
		if(S2->vf)
		{	TLG b =S2->vf;
			int x =	*(int *)(b->data);
			if(res < i -x)
			res = i - x;
		}
		else
		push(S3,&y);
		pop(S1);
	}
	eliberareq(C);
	eliberares(S);
	eliberares(S1);
	eliberares(S2);
	eliberares(S3);
	free(C);
	free(S);
	free(S1);
	free(S2);
	free(S3);	
	return res;
}	
int main (int argc,char *argv[])
{
  INF inf;
  int nr1, nr2, nr3, k,j,i;
  char operation[10];
  int id_stiva, id_coada;
  Coada *a;
  Stiva *s;
  FILE *f = fopen (argv[1],"r");
  FILE *g = fopen (argv[2],"w");
  if(!f) return 0;
  if(!g) return 0; 
  fscanf (f, "%d", &nr1);
  fscanf (f, "%d", &nr2);
  fscanf (f, "%d", &nr3); 
  a = malloc (nr3 * sizeof (Coada));
  s = malloc (nr2 * sizeof (Stiva));
   //Initializarea stivelor
  for (i = 0; i < nr2; i++)
    {
      InitS (&s[i], sizeof (INF));
      s[i].dim = sizeof(INF);
    }
    //Initializarea cozilor  
  for (i = 0; i < nr3; i++)
    {
      InitQ (&a[i], sizeof (INF));
      a[i].dim = sizeof(INF);
    }
//Efectuarea operatiilor
  for (j = 1; j <= nr1; j++)
    {
      fscanf (f, "%s", operation);
      if (strcmp (operation, "push") == 0)
	{
	  fscanf (f, "%d", &id_stiva);
	  fscanf (f, "%d", &inf.id_paranteza);
	  fscanf (f, " %c", &inf.tip);
	  push (&s[id_stiva], &inf);
	}
      else if (strcmp (operation, "intrq") == 0)
	{
	  fscanf (f, "%d", &id_coada);
	  fscanf (f, "%d", &inf.id_paranteza);
	  fscanf (f, " %c", &inf.tip);
	  intrq (&a[id_coada], &inf);
	}
      else if (strcmp (operation, "corrects") == 0)
	{
	  fscanf (f, "%d", &id_stiva);
          fprintf(g,"%d\n",corrects(&s[id_stiva]));
	}
      else if (strcmp (operation, "correctq") == 0)
	{
	  fscanf (f, "%d", &id_coada);
	  fprintf(g,"%d\n",correctq(&a[id_coada]));
	}
      else if (strcmp (operation, "pop") == 0)
	{
	  fscanf (f, "%d", &id_stiva);
	  pop (&s[id_stiva]);

	}
      else if (strcmp (operation, "extrq") == 0)
	{
	  fscanf (f, "%d", &id_coada);
	  extrq (&a[id_coada]);

	}
      else if (strcmp (operation, "sorts") == 0)
	{
	  fscanf (f, "%d", &id_stiva);
	  sorts (&s[id_stiva]);

	}
      else if (strcmp (operation, "sortq") == 0)
	{
	  fscanf (f, "%d", &id_coada);
	  sortq (&a[id_coada]);
	  
	}
      else if (strcmp (operation, "prints") == 0)
	{
	  for (k = 0; k < nr2; k++)
	    prints (&s[k],g);
	}
      else if (strcmp (operation, "printq") == 0)
	{
	  for (k = 0; k < nr3; k++)
	    printq (&a[k],g);
	}
    }  
      for(i = 0;i < nr2;i ++)
	eliberares(&s[i]);
      for(i = 0;i < nr3;i ++)
	eliberareq(&a[i]); 
	free(a);
	free(s);
  fclose (f);
  fclose (g);
  return 0;
}
