#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
int c1=0,c=0,c2=0,c3=0;
struct doctores {
	char IDs[10];
	char NombreC[' '];
	char especialidad[' '];
	char correo[' '];
	char tel[12];
	int tarifa;
	struct doctores *siguiente;
};
typedef struct doctores DOC;
typedef DOC *DOCSIG;
struct consultorios {
	char IDc[5];
	char claveC[10];
	char IDd[10];
	char IDp[10];
};
typedef struct consultorios CONSULTORIO;
typedef CONSULTORIO *CONSSIG;
struct PacienteI {
	char ID[10];
	char Nombre[' '];
	char telefono[12];
	char correo[' '];
	char NSS[15];
	char Enfermedad[30];
	char Habitacion[8];
	char descripcion[' '];
	struct PacienteI *sig;
};
typedef struct PacienteI PACIENTE;
typedef PACIENTE *PASSIG;
struct PacienteC {
	char ID[10];
	char Nombre[' '];
	char telefono[12];
	char correo[' '];
	char NSS[15];
	char descripcion[' '];
	char consultorio[3];
	struct PacienteC *sig;
};
typedef struct PacienteC PACIENTEC;
typedef PACIENTEC *PASCSIG;
CONSULTORIO Cons[50];
void doctor(DOCSIG *lista);
void ingreso(PASSIG *lista);
void inicializarDoctor(DOCSIG *lista);
void inicializarGeneral(PASCSIG *lista);
void inicializarIngreso(PASSIG *ingreso);
void cuenta(PASCSIG *Consulta, PASSIG *Ingreso, DOCSIG *doctores);
void busqueda(DOCSIG *lista,PASSIG *pasiente,PASCSIG *consulta);
void consultaG(PASCSIG *consulta);
void busquedaPacientesPiso();  //Funcion que busca los pacientes ordenados por piso
void busquedaPacientesTodos();	//Funcion que muestra la lista de todos los pacientes sin orden
void busquedaPiso(char auxl);  //Funcion que busca las habitaciones disponibles
void busquedaDoctores();   //Funcion que muestra una lista de todos los doctores
int validarEntero();
void eliminarPacienteI(PASSIG *lista, char *ID);
void eliminarPacienteC(PASCSIG *lista, char *ID);
void nuevoPacienteC(PASCSIG *consulta, char *consultorio);
void nuevoPacienteI(PASSIG *ingreso, char *consultorio, char *enfermedad);
char enlistarPacientesC(PASCSIG *consulta, FILE *gen);
void enlistarPacientesI(PASSIG *ingreso, FILE *ing);

int main(void) {
	char opc;
	int i;
	DOCSIG listadoc=NULL;
	PASSIG listaing=NULL;
	PASCSIG listagen=NULL;
	inicializarDoctor(&listadoc);
	FILE *Con;
	Con=fopen("CONSULTORIO.txt","r");
	if(Con!=NULL) {
		c1=0;
		while (!feof(Con)) {
			fscanf(Con,"%s",&Cons[c1].IDc);
			fscanf(Con,"%s",&Cons[c1].claveC);
			fscanf(Con,"%s",&Cons[c1].IDd);
			fscanf(Con,"%s",&Cons[c1].IDp);
			c1++;
		}
		fclose(Con);
	} else if(Con==NULL) {
		Con=fopen("CONSULTORIO.txt","w");
		for(i=0; i<10; i++) {
			fprintf(Con,"%d\n",100+i);
			fprintf(Con,"%d\n",100+i);
			fprintf(Con,"%d\n",0);
			fprintf(Con,"%d\n",0);
		}
		for(i=0; i<10; i++) {
			fprintf(Con,"%d\n",200+i);
			fprintf(Con,"%d\n",200+i);
			fprintf(Con,"%d\n",0);
			fprintf(Con,"%d\n",0);
		}
		for(i=0; i<10; i++) {
			fprintf(Con,"%d\n",300+i);
			fprintf(Con,"%d\n",300+i);
			fprintf(Con,"%d\n",0);
			fprintf(Con,"%d\n",0);
		}
		for(i=0; i<10; i++) {
			fprintf(Con,"%d\n",400+i);
			fprintf(Con,"%d\n",400+i);
			fprintf(Con,"%d\n",0);
			fprintf(Con,"%d\n",0);
		}
		for(i=0; i<10; i++) {
			fprintf(Con,"%d\n",500+i);
			fprintf(Con,"%d\n",500+i);
			fprintf(Con,"%d\n",0);
			fprintf(Con,"%d",0);
			if(i<9) {
				fprintf(Con,"\n");
			}
		}
		fclose(Con);
		Con=fopen("CONSULTORIO.txt","r");
		c1=0;
		while (!feof(Con)) {
			fscanf(Con,"%s",&Cons[c1].IDc);
			fscanf(Con,"%s",&Cons[c1].claveC);
			fscanf(Con,"%s",&Cons[c1].IDd);
			fscanf(Con,"%s",&Cons[c1].IDp);
			c1++;
		}
		fclose(Con);
	}
	inicializarIngreso(&listaing);
	inicializarGeneral(&listagen);
	do {
		printf("Seleccione una opcion\n\t1)Doctor\n\t2)Consulta General\n\t3)Ingreso\n\t4)Cuenta\n\t5)Busquedas\n\t6)Salir\n");
		fflush(stdin);
		scanf("%c",&opc);
		if(opc>'6'||opc<1)
			printf("Opcion ingresada no valida :(\n");
	} while(opc>'6'||opc<1);
	while(opc!='6') {
		switch(opc) {
			case '1':
				doctor(&listadoc);
				break;
			case '2':
				consultaG(&listagen);
				break;
			case '3':
				ingreso(&listaing);
				break;
			case '4':
				cuenta(&listagen,&listaing,&listadoc);
				break;
			case '5':
				busqueda(&listadoc,&listaing,&listagen);
				break;

		}
		do {
			system("cls");
			printf("Seleccione una opcion\n\t1)Doctor\n\t2)Consulta General\n\t3)Ingreso\n\t4)Cuenta\n\t5)Busquedas\n\t6)Salir\n");
			fflush(stdin);
			scanf("%c",&opc);
			if(opc>'6'||opc<1)
				printf("Opcion ingresada no valida :(\n");
		} while(opc>'6'||opc<1);
	}
}
void eliminarPacienteI(PASSIG *lista, char *ID) {
	PASSIG actual, previo, temporal;

	previo=*lista;
	actual=(*lista)->sig;

	if(strcmp(ID, previo->ID)==0) {
		temporal = *lista;
		*lista = (*lista)->sig;
		free(temporal);
	}
	while(actual != NULL) {
		if(strcmp(ID, previo->ID) == 0) {
			break;
		}
		previo = actual;
		actual = actual->sig;
	}
	if(actual != NULL) {
		temporal = actual;
		previo->sig = actual->sig;
		free(temporal);
	}
	printf("\nID no encontrado");
}

void eliminarPacienteC(PASCSIG *lista, char *ID) {
	PASCSIG actual, previo, temporal;

	previo=*lista;
	actual=(*lista)->sig;
	printf("\njejejeje");
	if(strcmp(ID, previo->ID)==0) {
		temporal = *lista;
		*lista = (*lista)->sig;
		free(temporal);
		return;
	}
	printf("\njejejejex2");
	while(actual != NULL) {
		if(strcmp(ID, previo->ID) == 0) {
			break;
		}
		previo = actual;
		actual = actual->sig;
	}
	printf("\njejejejex3");
	if(actual != NULL) {
		temporal = actual;
		previo->sig = actual->sig;
		free(temporal);
		return;
	}
	printf("\njejejejex4");
	printf("\nID no encontrado");
}

void inicializarDoctor(DOCSIG *lista) {
	DOCSIG nuevo;
	char cadena[' '];
	FILE *Doc;
	Doc=fopen("DOCTOR.txt","r");
	if(Doc!=NULL) {
		while (!feof(Doc)) {
			nuevo=malloc(sizeof(DOC));
			if(nuevo!=NULL) {
				fscanf(Doc," %[^\n]",nuevo->IDs);
				fscanf(Doc," %[^\n]",nuevo->NombreC);
				fscanf(Doc," %[^\n]",nuevo->especialidad);
				fscanf(Doc,"%s",nuevo->correo);
				fscanf(Doc,"%s",nuevo->tel);
				fscanf(Doc,"%s",cadena);
				nuevo->tarifa = atoi(cadena);
				if(nuevo->tarifa!=0) {
					nuevo->siguiente=(*lista);
					(*lista)=nuevo;
					c++;
				}
			}
		}
		fclose(Doc);
	} else {
		Doc=fopen("DOCTOR.txt","a");
		fclose(Doc);
	}
}
void inicializarIngreso(PASSIG *lista) {
	FILE *Ing;
	PASSIG nuevo;
	Ing=fopen("PACIENTEINGRESO.txt","r");
	if(Ing!=NULL) {
		while (!feof(Ing)) {
			nuevo=malloc(sizeof(PACIENTE));
			if(nuevo!=NULL) {
				fscanf(Ing,"%s",nuevo->ID);
				fscanf(Ing," %[^\n]",nuevo->Nombre);
				fscanf(Ing,"%s",nuevo->telefono);
				fscanf(Ing,"%s",nuevo->correo);
				fscanf(Ing,"%s",nuevo->NSS);
				fscanf(Ing," %[^\n]",nuevo->Enfermedad);
				fscanf(Ing," %[^\n]",nuevo->Habitacion);
				fscanf(Ing," %[^\n]",nuevo->descripcion);

				nuevo->sig=(*lista);
				(*lista)=nuevo;
				c2++;

			}
		}
		fclose(Ing);
	} else {
		Ing=fopen("PACIENTEINGRESO.txt","a");
		fclose(Ing);
	}
}
char enlistarPacientesC(PASCSIG *consulta, FILE *gen) {
	PASCSIG nuevo;
	nuevo=malloc(sizeof(PACIENTEC));
	if(nuevo != NULL) {
		fscanf(gen,"%s",nuevo->ID);
		fscanf(gen," %[^\n]",nuevo->Nombre);
		fscanf(gen,"%s",nuevo->telefono);
		fscanf(gen,"%s",nuevo->correo);
		fscanf(gen,"%s",nuevo->NSS);
		fscanf(gen," %[^\n]",nuevo->descripcion);
		fscanf(gen,"%s",nuevo->consultorio);
		nuevo->sig=(*consulta);
		(*consulta)=nuevo;
		return 'a';
	} else
		return 'b';
}

void inicializarGeneral(PASCSIG *lista) {
	int i;
	FILE *gen;
	PASCSIG nuevo;

	gen=fopen("PACIENTECONSULTA.txt","r");
	if(gen!=NULL) {
		while (!feof(gen)) {
			if(enlistarPacientesC(lista, gen) == 'a') {
				c2++;
			}
		}
		fclose(gen);
	} else if(gen==NULL) {
		gen=fopen("PACIENTECONSULTA.txt","w");
		fclose(gen);
		gen=fopen("PACIENTECONSULTA.txt","r");
		while (!feof(gen)) {
			fscanf(gen,"%s",nuevo->ID);
			fscanf(gen," %[^\n]",nuevo->Nombre);
			fscanf(gen,"%s",nuevo->telefono);
			fscanf(gen,"%s",nuevo->correo);
			fscanf(gen,"%s",nuevo->NSS);
			fscanf(gen," %[^\n]",nuevo->descripcion);
			fscanf(gen,"%s",nuevo->consultorio);
			nuevo->sig=(*lista);
			(*lista)=nuevo;
			c3++;
		}
		fclose(gen);
	}
}

void doctor(DOCSIG *lista) {
	system("cls");
	FILE *Doc;
	FILE *Con;
	DOCSIG aux,nuevo,aux2;
	char cadena[' '],opc1;
	int x,esp,i,j,opc2,contador;
	int x1;
	char ID[' '],ID1[' '];
	do {
		fflush(stdin);
		printf("Seleccione una opcion\n\t1)Nuevo Doctor\n\t2)Asignacion doctor\n\t3)Editar\n\t4)Regresar\n");
		scanf("%c",&opc1);
		if(opc1>'4'||opc1<'1')
			printf("Opcion ingresada no valida :(\n");
	} while(opc1>'4'||opc1<'1');
	while(opc1!='4') {
		switch(opc1) {
			case '1':
				nuevo=malloc(sizeof(DOC));
				if(nuevo!=NULL&&c<50) {

					do {
						x=1;
						printf("Ingrese la ID del doctor\n");
						fflush(stdin);
						scanf("%s",cadena);
						aux=(*lista);
						while(aux!=NULL) {
							if(strcmp(aux->IDs,cadena)==0) {
								x=0;
							}
							aux=aux->siguiente;
						}
						if(x==0) {
							printf("El ID ingresado ya existe :(\n");
						}
					} while(x==0);
					strcpy(nuevo->IDs,cadena);
					fflush(stdin);
					printf("Ingrese el nombre completo del doctor: ");
					fflush(stdin);
					gets(nuevo->NombreC);
					do {
						x=1;
						printf("Seleccione la su especialidad\n1)General\n2)Cardiologia\n3)Pediatria\n4)Urgencias\n5)Cirugia\n");
						scanf("%c",&opc1);
						switch(opc1) {
							case '1':
								strcpy(nuevo->especialidad,"General");
								break;
							case '2':
								strcpy(nuevo->especialidad,"Cardiologia");
								break;
							case '3':
								strcpy(nuevo->especialidad,"Pediatria");
								break;
							case '4':
								strcpy(nuevo->especialidad,"Urgencias");
								break;
							case '5':
								strcpy(nuevo->especialidad,"Cirugia");
								break;
							default:
								printf("Opcion no valida\n");
								x=0;
								break;
						}
					} while(x!=1);
					printf("Ingrese su correo: ");
					fflush(stdin);
					scanf("%s",nuevo->correo);
					printf("Ingrese su telefono: ");
					fflush(stdin);
					scanf("%s",nuevo->tel);
					printf("Ingrese tarifa por consulta: ");
					nuevo->tarifa=validarEntero();
					nuevo->siguiente=(*lista);
					(*lista)=nuevo;
					aux2 = *lista;
					Doc = fopen("DOCTOR.txt","w");
					contador=0;
					while(aux2!=NULL) {
						if(contador!=0) {
							fprintf(Doc,"\n");
						}
						fprintf(Doc,"%s\n",aux2->IDs);
						fprintf(Doc,"%s\n",aux2->NombreC);
						fprintf(Doc,"%s\n",aux2->especialidad);
						fprintf(Doc,"%s\n",aux2->correo);
						fprintf(Doc,"%s\n",aux2->tel);
						fprintf(Doc,"%d",aux2->tarifa);
						aux2 = aux2->siguiente;
						contador++;
					}
					fclose(Doc);
					fflush(stdin);
				}

				break;
			case '2':
				x1=0;
				aux=(*lista);
				while(aux!=NULL) {
					x=1;
					for(i=0; i<c1; i++) {
						if(strcmp(Cons[i].IDd,aux->IDs)==0) {
							x=0;
						}
					}
					if(x==1) {
						printf("El doctor %s con el ID %s esta disponible\n",aux->NombreC,aux->IDs);
						x1++;
					}
					aux=aux->siguiente;
				}
				if(x1==0) {
					printf("No hay doctores disponibles, por favor dar de alta a un nuevo doctor \n");
					break;
				}

				printf("\n\n");
				for(i=0; i<c1; i++) {
					if(strcmp(Cons[i].IDd,"0")==0) {
						printf("El consultorio %s esta disponible\n",Cons[i].IDc);
					}
				}
				do {
					printf("Ingrese el ID del doctor que desea asignar: ");
					fflush(stdin);
					scanf("%s",ID1);
					aux=(*lista);
					while(aux!=NULL) {
						if(strcmp(aux->IDs,ID1)==0) {
							x=0;
						}
						aux=aux->siguiente;
					}
					for(i=0; i<c1; i++) {
						if(strcmp(ID1,Cons[i].IDd)==0) {
							x==1;
						}
					}
					if(x!=0) {
						printf("El ID ingresado no pertenece a ningun doctor disponible\nIngrese una Id valida\n");
					}
				} while(x!=0);
				do {
					x=1;
					printf("Ingrese el numero de la habitacion a la que se quiere asignar el doctor: ");
					fflush(stdin);
					scanf("%s",ID);
					for(i=0; i<c1; i++) {
						if(strcmp(ID,Cons[i].IDc)==0&&strcmp(Cons[i].IDd,"0")==0) {
							x=0;
						}
					}
					if(x!=0) {
						printf("El ID ingresado no pertenece a ninguna habitacion disponible :(\n");
					}

				} while(x!=0);
				for(i=0; i<c1; i++) {
					if(strcmp(ID,Cons[i].claveC)==0) {
						strcpy(Cons[i].IDd,ID1);
					}
				}
				printf("Se ha asignado el doctor correctamente\n");
				Con=fopen("Consultorio.txt","w");
				for(i=0; i<c1; i++) {
					fprintf(Con,"%s\n",Cons[i].IDc);
					fprintf(Con,"%s\n",Cons[i].claveC);
					fprintf(Con,"%s\n",Cons[i].IDd);
					fprintf(Con,"%s",Cons[i].IDp);
					if(i<c1-1) {
						fprintf(Con,"\n");
					}
				}
				fclose(Con);
				fflush(stdin);
				break;
			case '3':
				do {
					x=0;
					printf("Ingrese el ID del doctor que desea modificar sus datos: ");
					fflush(stdin);
					scanf("%s",ID);
					aux=(*lista);
					while(aux!=NULL) {
						if(strcmp(ID,aux->IDs)==0) {
							do {
								printf("Ingrese la opcion del dato desea modificar del doctor\n1)Correo\n2)Telefono\n3)Tarifa de consulta\n4)Regresar\n");
								scanf("%d",&opc2);
								switch(opc2) {
									case 1:
										printf("Ingrese el nuevo correo del medico\n");
										scanf("%s",aux->correo);
										break;
									case 2:
										printf("Ingrese el nuevo telefono del medico\n");
										scanf("%s",aux->tel);
										break;
									case 3:
										printf("Ingrese la nueva tarifa por consulta del medico\n");
										aux->tarifa=validarEntero();
										break;
									case 4:
										break;
									default:
										printf("Opcion no valida\n");
										getch();
										system("cls");
								}
							} while(opc2!=4);
							system("cls");
							aux2 = *lista;
							Doc = fopen("DOCTOR.txt","w");
							contador=0;
							while(aux2!=NULL) {
								if(contador!=0) {
									fprintf(Doc,"\n");
								}
								fprintf(Doc,"%s\n",aux2->IDs);
								fprintf(Doc,"%s\n",aux2->NombreC);
								fprintf(Doc,"%s\n",aux2->especialidad);
								fprintf(Doc,"%s\n",aux2->correo);
								fprintf(Doc,"%s\n",aux2->tel);
								fprintf(Doc,"%d",aux2->tarifa);
								aux2 = aux2->siguiente;
								contador++;
							}
							fclose(Doc);
							x=1;
						}
						aux=aux->siguiente;
					}
					if(x!=1)
						printf("Ningun doctor tiene asignado el ID ingresado :( \n");
				} while(x!=1);
				break;
		}
		do {
			system("pause");
			system("cls");
			printf("Seleccione una opcion\n\t1)Nuevo Doctor\n\t2)Asignacion doctor\n\t3)Editar\n\t4)Regresar\n");
			scanf("%c",&opc1);
			if(opc1>'4'||opc1<'1')
				printf("Opcion ingresada no valida :(\n");
		} while(opc1>'4'||opc1<'1');
	}
	fflush(stdin);
}
void ingreso(PASSIG *lista) {
	int aux,aux1,x,i,x1;
	FILE *Ing;
	FILE *Con;
	PASSIG nuevo,aux2;
	char p;
	fflush(stdin);
	printf("     INGRESO DEL PACIENTE    \n\n");
	nuevo=malloc(sizeof(PACIENTE));
	if(nuevo!=NULL&&c2<40) {

		do {
			printf("\n%cQue enfermedad tiene el paciente?\n1)Arritmia Cardiaca\n2)Hipertension Arterial\n3)Infarto Miocardio Agudo\n4)Asma\n5)Reflujo Gastroesofagico\n6)Neumonia\n7)Fractura\n8)Contusion cerebral\n9)Traumatismo craneoencefalico\n10)Trasplantes\n11)Fractura nasal\n    Opcion Elegida:",168);
			scanf("%d", &aux);
		} while(aux<1||aux>12);
		switch(aux) {
			case 1:
				strcpy(nuevo->Enfermedad,"Arritmia Cardiaca");
				p='2';
				aux1=20;
				break;
			case 2:
				strcpy(nuevo->Enfermedad,"Hipertension Arterial");
				p='2';
				aux1=20;
				break;
			case 3:
				strcpy(nuevo->Enfermedad,"Infarto Miocardio Agudo");
				p='2';
				aux1=20;
				break;
			case 4:
				strcpy(nuevo->Enfermedad,"Asma");
				p='3';
				aux1=30;
				break;
			case 5:
				strcpy(nuevo->Enfermedad,"Reflujo Gastroesofagico");
				p='3';
				aux1=30;
				break;
			case 6:
				strcpy(nuevo->Enfermedad,"Neumonia");
				p='3';
				aux1=30;
				break;
			case 7:
				strcpy(nuevo->Enfermedad,"Fractura");
				p='4';
				break;
			case 8:
				strcpy(nuevo->Enfermedad,"Contusion Cerebral");
				p='4';
				aux1=40;
				break;
			case 9:
				strcpy(nuevo->Enfermedad,"Traumatismo Craneoencefalico");
				p='4';
				break;
			case 10:
				strcpy(nuevo->Enfermedad,"Transplantes");
				p='5';
				break;
			case 11:
				strcpy(nuevo->Enfermedad,"Fractura Nasal");
				p='5';
				break;
		}
		busquedaPiso(p);
		int auxn=0;
		do {
			x1=0;
			auxn=0;
			printf("Seleccione la habitacion: ");
			scanf("%s",nuevo->Habitacion);
			for(i=(p-49)*10; i<(p-48)*10; i++) {
				if(strcmp(nuevo->Habitacion,Cons[i].IDc)==0) {
					if(strcmp("0",Cons[i].IDp)==0&&strcmp("0",Cons[i].IDd)!=0) {
						x1++;
					}
				}
			}
			if(x1!=0) {
				for(i=(p-49)*10; i<(p-48)*10; i++) {
					if(strcmp(nuevo->Habitacion,Cons[i].IDc)==0) {
						if(strcmp("0",Cons[i].IDp)==0&&strcmp("0",Cons[i].IDd)!=0) {
							printf("Operacion exitosa\n");
							i=c1;
						} else {
							printf("La habitacion no esta disponible\n");
							auxn=1;
							i=c1;
						}
					}
				}
			} else {
				printf("No hay habitaciones disponibles en el piso deseado\n");
				auxn=2;
				getch();
				break;
			}
		} while(auxn==1);
		if(auxn==2) {
		} else {
			for(i=0; i<c1; i++) {
				if(!strcmp(Cons[i].IDc,nuevo->Habitacion)) {
					strcpy(Cons[i].IDp,nuevo->ID);
				}
			}
			printf("\nDescriba la enfermedad a detalle:\n");
			fflush(stdin);
			gets(nuevo->descripcion);

			Ing=fopen("PACIENTEINGRESO.txt", "r+");
			fprintf(Ing,"%s\n", nuevo->ID);
			fprintf(Ing,"%s\n", nuevo->Nombre);
			fprintf(Ing,"%s\n", nuevo->telefono);
			fprintf(Ing,"%s\n",nuevo->correo);
			fprintf(Ing,"%s\n", nuevo->NSS);
			fprintf(Ing,"%s\n",nuevo->Enfermedad);
			fprintf(Ing,"%s\n", nuevo->Habitacion);
			fprintf(Ing,"%s",nuevo->descripcion);
			fclose(Ing);
			c2++;
			Con=fopen("CONSULTORIO.txt","w");
			for(i=0; i<50; i++) {
				fprintf(Con,"%s\n",Cons[i].IDc);
				fprintf(Con,"%s\n",Cons[i].claveC);
				fprintf(Con,"%s\n",Cons[i].IDd);
				fprintf(Con,"%s",Cons[i].IDp);
				if(i<49) {
					fprintf(Con,"\n");
				}
			}
			fclose(Con);
		}

	}


}
int validarEntero() { //Esta funcion sirve para validar que una entrada por teclado sea un numero entero
	int i=0,aux,j,num=0;
	char entero[' ']; //Se utilizara una cadena para verificar que cada caracter sea un digito
	do {
		aux=0;
		fflush(stdin);
		gets(entero);	//Se lee la cadena
		while(entero[i]!='\0') { //Se recorre la cadena cadena para verificar que todos los caracteres sean digitos
			if(entero[i]<48||entero[i]>57) {
				aux=1;
				printf("El elemento ingresado no es valido\nIngrese de nuevo: "); //Se informa al usuario que ingreso datos invalidos
				entero[i+1]='\0';	//Instruccion para detener el ciclo
			}
			i++;
		}
	} while(aux==1);
	i=strlen(entero); //A la variable i  se le asigna la longitud de la cadena que representa el entero
	for(j=1; j<=i; j++) { //ciclo para convertir la cadena a entero digito por dogito
		num+=(entero[j-1]-48)*pow(10,i-j); //  La cadena ingresada se convierte a numero entero
	}
	return num;
}
void cuenta(PASCSIG *consulta, PASSIG *ingreso, DOCSIG *doctores) {
	FILE *pago;
	FILE *Con;
	FILE *gen;
	FILE *Ing;
	PASCSIG actual, previo;
	PASSIG current, previous;
	DOCSIG doc;
	int op,i,x,precio,op2,aux,dias;
	int po; //posibles opciones
	char ID[10],ID1[20];
	char op1;
	do {
		system("cls");
		precio=0;
		po=0;
		printf("Ingrse la opcion que desea realizar\n1)Cobro de consulta general\n2)Cobro de estancia\n3)Regresar\n");
		scanf("%d",&op);
		switch(op) {
			case 1:
				for(i=0 ; i<c1; i++) {
					if(strcmp("0",Cons[i].IDp) == 0) {
						po++;
					}
				}
				if(po==0) {
					printf("No hay pacientes actualmente en consulta general\n");
					getch();
					break;
				} else {
					do {
						fflush(stdin);
						printf("Ingrese un ID valido de un paciente: ");
						gets(ID);
						actual = *consulta;
						while(actual != NULL) {
							if(strcmp(ID, actual->ID) == 0) {
								break;
							}
							actual = actual->sig;
						}
						if(actual == NULL) {
							printf("El ID ingresado no existe...\n");
						}
					} while(actual == NULL);

					eliminarPacienteC(consulta, ID);
					for(i = 0; i<10; i++) {
						if(strcmp(ID,Cons[i].IDp) != 0) {
							strcpy(Cons[i].IDp,"0");
							strcpy(ID1,Cons[i].IDd);
							strcpy(Cons[i].IDd, "0");
							break;
						}
					}

					Con=fopen("CONSULTORIO.txt","w");
					for(i=0; i<c1; i++) {
						fprintf(Con,"%s\n",Cons[i].IDc);
						fprintf(Con,"%s\n",Cons[i].claveC);
						fprintf(Con,"%s\n",Cons[i].IDd);
						fprintf(Con,"%s",Cons[i].IDp);
						if(i<c1-1) {
							fprintf(Con,"\n");
						}
					}
					fclose(Con);
					gen=fopen("PACIENTECONSULTA.txt","w");
					while(*consulta != NULL) {
						fprintf(gen,"%s\n",(*consulta)->ID);
						fprintf(gen,"%s\n",(*consulta)->Nombre);
						fprintf(gen,"%s\n",(*consulta)->telefono);
						fprintf(gen,"%s\n",(*consulta)->correo);
						fprintf(gen,"%s\n",(*consulta)->NSS);
						fprintf(gen,"%s\n",(*consulta)->descripcion);
						fprintf(gen,"%s\n",(*consulta)->consultorio);
						*consulta = (*consulta)->sig;
					}
					fclose(gen);
					doc = *doctores;
					while(doc!= NULL) {
						if(strcmp(ID1, doc->IDs) == 0) {
							break;
						}
						doc = doc->siguiente;
					}
					if(doc != NULL) {
						precio = doc->tarifa;
					}
					pago=fopen("ticket.txt","w");
					fprintf(pago,"		Hospital San Bisonte		\n----------------------------------------------------------------\n	ID del peciente: %s\n\n",Cons[aux].IDp);
					fprintf(pago,"		$%d.....Cobro por consulta\n",precio);
					do {
						printf("Desea hacer un cargo extra (s/n)\n");
						scanf("%c",&op1);
						fflush(stdin);
						if(op1 == 's' && op1 == 'n') {

							switch(op1) {
								case 's':
									do {
										printf("Selecione el cargo extra que se realizo\n1)Electrocardiograma $5,000\n2)Prueba de esfuerzo $3,500\n3)Apendicectomia $12,600\n4)Biopsias $6,000\n5)Bypass Gastrico $12,000\n6)Histerectomia $8,000\n7)Liposuccion $15,000\n8)Trasplante de corne $20,000\n9)Ecocardiograma transesofagico $5,000\n");
										scanf("%d",&op2);
										if(op2 >= 1 && op2 <= 9) {
											switch (op2) {
												case 1:
													precio+=5000;
													fprintf(pago,"		$5,000.....Electrocardiograma\n");
													break;
												case 2:
													precio+=3500;
													fprintf(pago,"		$3,500.....Prueba de esfuerzo\n");
													break;
												case 3:
													precio+=12600;
													fprintf(pago,"		$12,600.....Apendicectomia\n");
													break;
												case 4:
													precio+=6000;
													fprintf(pago,"		$6,000.....Biopsias\n");
													break;
												case 5:
													precio+=12000;
													fprintf(pago,"		$12,000.....Bypass Gastrico\n");
													break;
												case 6:
													precio+=8000;
													fprintf(pago,"		$8,000.....Histerectomia\n");
													break;
												case 7:
													precio+=15000;
													fprintf(pago,"		$15,000.....Liposuccion\n");
													break;
												case 8:
													precio+=20000;
													fprintf(pago,"		$20,000.....Trasplante de corne\n");
													break;
												case 9:
													fprintf(pago,"		$5,000.....Ecocardiograma transesofagico\n");
													precio+=5000;
													break;
											}
										} else
											printf("\nOpcion no especificada...\n");
										fflush(stdin);
									} while(op2<1 || op2>9);
							}
						} else
							printf("\nOpcion no especificada...\n");
					} while(op1!='n');


					fprintf(pago,"----------------------------------------------------------------\n		$%d.....Total a pagar\n",precio);
					fclose(pago);
					break;
				}
			case 2:
				for(i=10; i<c1; i++) {
					if(strcmp("0",Cons[i].IDp)) {
						po++;
					}
				}
				if(po==0) {
					printf("No hay pacientes actualmente en consulta general\n");
					getch();
					break;
				} else {
					do {
						x=1;
						for(i=10; i<c1; i++) {
							if(strcmp("0",Cons[i].IDp)) {
								po++;
							}
						}
						if(po==0) {
							printf("No hay pacientes actualmente en consulta general\n");
							getch();
							break;
						}
						printf("Ingrese la ID del paciente\n");
						scanf("%s",ID);
						fflush(stdin);
						for(i=10; i<c1; i++) {
							if(!strcmp(ID,Cons[i].IDp)) {
								x=0;
								aux=i;
							}
						}
						if(x!=0) {
							printf("La ID ingresada no pertenece a ningun paciente\n");
						}
					} while(x!=0);
					do {
						printf("Ingrese el numero de dias que tuvo ingresado\n");
						scanf("%d",&dias);
						if(dias<=0) {
							printf("Ingrese una cantida valida de dias\n");
						}
					} while(dias<=0);
					pago=fopen("ticket.txt","w");
					fprintf(pago,"		Hospital San Bisonte		\n----------------------------------------------------------------\n	ID del peciente: %s\n\n",Cons[aux].IDp);
					for(i=10; i<c1; i++) {
						if(!strcmp(ID,Cons[i].IDp)) {
							strcpy(Cons[i].IDp,"0");
							strcpy(ID1,Cons[i].IDd);
							break;
						}
					}
					if(i>=10&&i<20) {
						precio=dias*8000;
					} else if(i>=20&&i<30) {
						precio=dias*7000;
					} else if(i>=30&&i<40) {
						precio=dias*5000;
					} else if(i>=40&&i<50) {
						precio=dias*10000;
					}
					eliminarPacienteI(ingreso, ID);
					Con=fopen("CONSULTORIO.txt","w");
					for(i=0; i<c1; i++) {
						fprintf(Con,"%s\n",Cons[i].IDc);
						fprintf(Con,"%s\n",Cons[i].claveC);
						fprintf(Con,"%s\n",Cons[i].IDd);
						fprintf(Con,"%s",Cons[i].IDp);
						if(i<c1-1) {
							fprintf(Con,"\n");
						}
					}
					fclose(Con);
					Ing=fopen("PACIENTEINGRESO.txt","w");
					for(i=0; i<40; i++) {
						fprintf(Ing,"%s\n",(*ingreso)->ID);
						fprintf(Ing,"%s\n",(*ingreso)->Nombre);
						fprintf(Ing,"%s\n",(*ingreso)->telefono);
						fprintf(Ing,"%s\n",(*ingreso)->correo);
						fprintf(Ing,"%s\n",(*ingreso)->NSS);
						fprintf(Ing,"%s\n",(*ingreso)->Enfermedad);
						fprintf(Ing,"%s\n",(*ingreso)->Habitacion);
						fprintf(Ing,"%s\n",(*ingreso)->descripcion);
						if(i<39) {
							fprintf(Ing,"\n");
						}
						(*ingreso) = (*ingreso)->sig;
					}
					fclose(Ing);

					fprintf(pago,"		$%d.....Cobro por estancia\n",precio);
					do {
						fflush(stdin);
						printf("Desea hacer un cargo extra (s/n)\n");
						scanf("%c",&op1);
						fflush(stdin);
						switch(op1) {
							case 's':
								do {
									printf("Selecione el cargo extra que se realizo\n1)Electrocardiograma $5,000\n2)Prueba de esfuerzo $3,500\n3)Apendicectomia $12,600\n4)Biopsias $6,000\n5)Bypass Gastrico $12,000\n6)Histerectomia $8,000\n7)Liposuccion $15,000\n8)Trasplante de corne $20,000\n9)Ecocardiograma transesofagico $5,000\n");
									scanf("%d",&op2);
									switch (op2) {
										case 1:
											precio+=5000;
											fprintf(pago,"		$5,000.....Electrocardiograma\n");
											break;
										case 2:
											precio+=3500;
											fprintf(pago,"		$3,500.....Prueba de esfuerzo\n");
											break;
										case 3:
											precio+=12600;
											fprintf(pago,"		$12,600.....Apendicectomia\n");
											break;
										case 4:
											precio+=6000;
											fprintf(pago,"		$6,000.....Biopsias\n");
											break;
										case 5:
											precio+=12000;
											fprintf(pago,"		$12,000.....Bypass Gastrico\n");
											break;
										case 6:
											precio+=8000;
											fprintf(pago,"		$8,000.....Histerectomia\n");
											break;
										case 7:
											precio+=15000;
											fprintf(pago,"		$15,000.....Liposuccion\n");
											break;
										case 8:
											precio+=20000;
											fprintf(pago,"		$20,000.....Trasplante de corne\n");
											break;
										case 9:
											fprintf(pago,"		$5,000.....Ecocardiograma transesofagico\n");
											precio+=5000;
											break;
										default:
											printf("Opcion no valida\n");
											break;
									}
									fflush(stdin);
								} while(op2<1||op2>9);
						}
					} while(op1!='n');
					fprintf(pago,"----------------------------------------------------------------\n		$%d.....Total a pagar\n",precio);
					fclose(pago);
					break;
				}
		}
	} while(op!=3);
	system("cls");
}

void busqueda(DOCSIG *lista,PASSIG *pasiente,PASCSIG *consulta) {
	char piso;
	char opc,sopc;
	system("cls");
	do {
		printf("Ingrese una opcion\n\t1)Habitaciones disponibles\n\t2)Pacientes\n\t3)Lista de doctores\n\t4)Listar Pacientes Consulta\n");
		fflush(stdin);
		scanf("%c",&opc);
		if(opc<'1'||opc>'4')
			printf("Opcion ingresada no valida\n");
	} while(opc<'1'||opc>'4');
	switch(opc) {
		case '1':
			do {
				printf("Ingrese el piso donde desea buscar: ");
				fflush(stdin);
				scanf("%c",&piso);
				if(piso<'2'||piso>'5')

				{
					if(piso=='1')
						printf("Dicho piso no contiene habitaciones, solo consultorios\n");
					else
						printf("El piso ingresado no existe\n");
				}
			} while(piso<'2'||piso>'5');
			busquedaPiso(piso);
			break;
		case '2':
			do {
				printf("Seleccione una opcion\n\t1)Por piso\n\t2)todos los pacientes\n");
				fflush(stdin);
				scanf("%c",&sopc);
				if(sopc<'1'||sopc>'2')
					printf("Opcion seleccionada no valida\n");
			} while(sopc<'1'||sopc>'2');
			switch(sopc) {
				case 49:
					busquedaPacientesPiso();
					break;
				case '2':
					busquedaPacientesTodos();
					break;
			}
			break;
		case '3':
			busquedaDoctores(lista);
			break;
	}
	system("pause");
	system("cls");
}
void busquedaPiso(char auxl) {
	char Piso[7]="Piso ",aux[2];
	int i;
	aux[0]=auxl;
	aux[1]=0;
	printf("Hospital San Bisonte\n");
	strcat(Piso,aux);
	printf("%s\t",Piso);
	switch(auxl) {
		case '2':
			printf("Cardiologia\n");
			break;
		case '3':
			printf("Pediatria\n");
			break;
		case '4':
			printf("Urgencias\n");
			break;
		case '5':
			printf("Cirugia\n");
			break;
	}
	printf("Habitaciones disponibles\n");
	for(i=0; i<c1; i++) {
		if(Cons[i].claveC[0]==auxl)
			if(strcmp(Cons[i].IDp,"0")==0&&strcmp(Cons[i].IDd,"0")!=0)
				printf("%s\n",Cons[i].claveC);
	}
}

void busquedaPacientesTodos(PASSIG *ingreso, PASCSIG *consulta) {
	int i;
	printf("Hospital San Bisonte\n");
	printf("Nombre Paciente  NSS Consultorio Descripcion\n");
	for(i=0; i<c2; i++) {
		printf("%s %s %s %s\n ", (*ingreso)->Nombre, (*ingreso)->NSS, (*ingreso)->Habitacion, (*ingreso)->descripcion);
	}
}
void busquedaPacientesPiso(PASCSIG *consulta, PASSIG *ingreso) {
	PASSIG actual;
	PASCSIG current;
	int i,j,z;
	printf("Hospital San Bisonte\n");
	for(i=2; i<6; i++) {
		switch(i) {
			case 2:
				printf("Piso 2: Cardiologia\n");
				for(j=0; j<2; j++) {
					actual = *ingreso;
					switch(j) {
						case 0:
							printf("Arritmia Cardiaca\n");
							for(z=0; z<c2; z++) {
								if(strcmp(actual->Enfermedad,"Arritmia Cardiaca")==0) {
									printf("%s %s %s %s\n",actual->Nombre, actual->NSS, actual->Habitacion, actual->descripcion);
								}
								actual = actual->sig;
							}
							break;
						case 1:
							printf("Hipertension Arterial\n");
							for(z=0; z<c2; z++) {
								if(strcmp(actual->Enfermedad,"Hipertension Arterial")==0) {
									printf("%s %s %s %s\n",actual->Nombre, actual->NSS, actual->Habitacion, actual->descripcion);
								}
								actual = actual->sig;
							}
							break;
						case 2:
							printf("Infarto Miocardio Agudo\n");
							for(z=0; z<c2; z++) {
								if(strcmp(actual->Enfermedad,"Infarto Miocardio Agudo")==0) {
									printf("%s %s %s %s\n",actual->Nombre, actual->NSS, actual->Habitacion, actual->descripcion);
								}
								actual = actual->sig;
							}
					}
				}
				break;
			case 3:
				printf("Piso 3: Pediatria\n");
				for(j=0; j<2; j++) {
					actual = *ingreso;
					switch(j) {
						case 0:
							printf("Asma\n");
							for(z=0; z<c2; z++) {
								if(strcmp(actual->Enfermedad,"Asma")==0) {
									printf("%s %s %s %s\n",actual->Nombre, actual->NSS, actual->Habitacion, actual->descripcion);
								}
								actual = actual->sig;
							}
							break;
						case 1:
							printf("Reflujo Gastroesofagico\n");
							for(z=0; z<c2; z++) {
								if(strcmp(actual->Enfermedad,"Reflujo Gastroesofagico")==0) {
									printf("%s %s %s %s\n",actual->Nombre, actual->NSS, actual->Habitacion, actual->descripcion);
								}
								actual = actual->sig;
							}
							break;
						case 2:
							printf("Neumonia\n");
							for(z=0; z<c2; z++) {
								if(strcmp(actual->Enfermedad,"Neumonia")==0) {
									printf("%s %s %s %s\n",actual->Nombre, actual->NSS, actual->Habitacion, actual->descripcion);
								}
								actual = actual->sig;
							}
					}
				}
				break;
			case 4:
				printf("Piso 4: Urgencias\n");
				for(j=0; j<2; j++) {
					actual = *ingreso;
					switch(j) {
						case 0:
							printf("Fractura\n");
							for(z=0; z<c2; z++) {
								if(strcmp(actual->Enfermedad,"Fractura")==0) {
									printf("%s %s %s %s\n",actual->Nombre, actual->NSS, actual->Habitacion, actual->descripcion);
								}
								actual = actual->sig;
							}
							break;
						case 1:
							printf("Contusion Cerebral\n");
							for(z=0; z<c2; z++) {
								if(strcmp(actual->Enfermedad,"Contusion Cerebral")==0) {
									printf("%s %s %s %s\n",actual->Nombre, actual->NSS, actual->Habitacion, actual->descripcion);
								}
								actual = actual->sig;
							}
							break;
						case 2:
							printf("Traumatismo craneoencefalico\n");
							for(z=0; z<c2; z++) {
								if(strcmp(actual->Enfermedad,"Traumatismo Craneoencefalico")==0) {
									printf("%s %s %s %s\n",actual->Nombre, actual->NSS, actual->Habitacion, actual->descripcion);
								}
								actual = actual->sig;
							}
							break;
					}
				}
				break;
			case 5:
				printf("Piso 5: Cirugia\n");
				for(j=0; j<2; j++) {
					actual = *ingreso;
					switch(j) {
						case 0:
							printf("Transplantes\n");
							for(z=0; z<c2; z++) {
								if(strcmp(actual->Enfermedad,"Transplantes")==0) {
									printf("%s %s %s %s\n",actual->Nombre, actual->NSS, actual->Habitacion, actual->descripcion);
								}
								actual = actual->sig;
							}
							break;
						case 1:
							printf("Fractura Nasal\n");
							for(z=0; z<c2; z++) {
								if(strcmp(actual->Enfermedad,"Fractura Nasal")==0) {
									printf("%s %s %s %s\n",actual->Nombre, actual->NSS, actual->Habitacion, actual->descripcion);
								}
								actual = actual->sig;
							}
					}
				}
				break;
		}
	}

}

void busquedaDoctores(DOCSIG *doctores) {
	system("cls");
	int i=1;
	DOCSIG actual;
	actual = *doctores;
	printf("Hospital San Bisonte\n\n");
	while(actual != NULL) {
		printf("Doctor #%d\n\n",i);
		printf("Nombre: %s\nEspacialidad: %s\nTelefono: %s\nCorreo: %s\nTarifa: %d\n\n\n",actual->NombreC, actual->especialidad, actual->tel,actual->correo,actual->tarifa);
		actual = actual->siguiente;
		i++;
	}
}

void nuevoPacienteC(PASCSIG *consulta, char *consultorio) {
	PASCSIG nuevo, actual;
	FILE *gen;
	nuevo=malloc(sizeof(PACIENTEC));
	int i;
	if(nuevo!=NULL) {
		strcpy(nuevo->consultorio, consultorio);
		do {
			fflush(stdin);
			printf("Ingrese un ID (Unico) al paciente: ");
			gets(nuevo->ID);
			actual = *consulta;
			while(actual != NULL) {
				if(strcmp(actual->ID, nuevo->ID) == 0) {
					break;
				}
				actual = actual->sig;
			}
			if(actual != NULL) {
				printf("El ID ingresado ya existe...\n");
			}
		} while(actual != NULL);

		printf("Ingrese el nombre completo del paciente\n");
		gets(nuevo->Nombre);
		printf("Ingrese el telefono del paciente\n");
		gets(nuevo->telefono);
		printf("Ingrese el correo del paciente\n");
		gets(nuevo->correo);
		printf("Ingrese el numero de seguro social del paciente\n");
		gets(nuevo->NSS);
		printf("Ingrese una descripcion de la enfermedad\n");
		gets(nuevo->descripcion);
		strcpy(nuevo->consultorio, consultorio);
		for(i = 0; i<10; i++) {
			if(strcmp(nuevo->consultorio, Cons[i].IDc) == 0) {
				strcpy(Cons[i].IDp, nuevo->ID);
				printf("\n*****Paciente asignado al consultorio %s******\n", Cons[i].IDc);
				system("pause");
				break;
			}
		}
		nuevo->sig = NULL;
		nuevo->sig = *consulta;
		*consulta = nuevo;

		gen=fopen("PACIENTECONSULTA.txt","w");
		actual = *consulta;
		int contador = 0;
		while(actual != NULL) {
			if(contador!=0) {
				fprintf(gen,"\n");
			}
			fprintf(gen,"%s\n",actual->ID);
			fprintf(gen,"%s\n",actual->Nombre);
			fprintf(gen,"%s\n",actual->telefono);
			fprintf(gen,"%s\n",actual->correo);
			fprintf(gen,"%s\n",actual->NSS);
			fprintf(gen,"%s\n",actual->descripcion);
			fprintf(gen,"%s",actual->consultorio);
			actual = actual->sig;
			contador++;
		}
		fclose(gen);
	}
}

void nuevoPacienteI(PASSIG *ingreso, char *consultorio, char *enfermedad) {
	PASSIG nuevo, actual;
	nuevo=malloc(sizeof(PACIENTE));
	if(nuevo!=NULL) {
		strcpy(nuevo->Habitacion, consultorio);
		do {
			fflush(stdin);
			printf("Ingrese un ID (Unico) al paciente: ");
			gets(nuevo->ID);
			actual = *ingreso;
			while(actual != NULL) {
				if(strcmp(actual->ID, nuevo->ID) == 0) {
					break;
				}
				actual = actual->sig;
			}
			if(actual != NULL) {
				printf("El ID ingresado ya existe...\n");
			}
		} while(actual != NULL);

		printf("Ingrese el nombre completo del paciente\n");
		gets(nuevo->Nombre);
		printf("Ingrese el telefono del paciente\n");
		gets(nuevo->telefono);
		printf("Ingrese el correo del paciente\n");
		gets(nuevo->correo);
		printf("Ingrese el numero de seguro social del paciente\n");
		gets(nuevo->NSS);
		printf("Ingrese una descripcion de la enfermedad\n");
		gets(nuevo->descripcion);
		strcpy(nuevo->Habitacion, consultorio);

		nuevo->sig = *ingreso;
		*ingreso = nuevo;
	}
}

void consultaG(PASCSIG *consulta) {
	FILE *Con;
	FILE *gen;
	PASCSIG actual;
	int i,x;
	for(i = 0; i< 10; i++) {
		if((strcmp(Cons[i].IDp, "0") == 0) && (strcmp(Cons[i].IDd, "0") != 0)) {
			break;
		}
	}
	if(i == 10) {
		printf("No hay habitaciones disponibles\n");
		return;
	}

	nuevoPacienteC(consulta, Cons[i].IDc);

	Con=fopen("CONSULTORIO.txt","w");
	for(i=0; i<c1; i++) {
		fprintf(Con,"%s\n",Cons[i].IDc);
		fprintf(Con,"%s\n",Cons[i].claveC);
		fprintf(Con,"%s\n",Cons[i].IDd);
		fprintf(Con,"%s",Cons[i].IDp);
		if(i<c1-1) {
			fprintf(Con,"\n");
		}
	}
	fclose(Con);

}


