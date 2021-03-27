/* lynx2wav RetroWiki tape converter*/
#define version "1.2"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define PI 3.14159265


FILE *in, *out;
int file_size;
int speed = 22050;
int tape_1 = 20;  // TAPE 3
int square = 0;

struct
{
	char sig[4];
	int riff_size;
	char typesig[4];
	char fmtsig[4];
	int fmtsize;
	short tag;
	short channels;
	int freq;
	int bytes_per_sec;
	short byte_per_sample;
	short bits_per_sample;
	char samplesig[4];
	int datalength;

}sample_riff= { "RIFF",0,"WAVE","fmt ",16,1,1,22050,22050,1,8,"data",0 }; 

int stricmp(const char *a, const char *b)
{
	int ca, cb;
	do
	{
		ca = (unsigned char)*a++;
		cb = (unsigned char)*b++;
		ca = tolower(toupper(ca));
		cb = tolower(toupper(cb));
	} while (ca == cb && ca != '\0');
	return ca - cb;
}


//static int current_level=223;
//void inverse_level() { current_level=255-current_level; }

void emit_silence(int size)
{
    int i;
	
    for (i=0;i<(size*speed);i++) {
		     
			  
			  fputc(0,out);
			  			
	}
	file_size+=size*speed;
}



void emit_square_level(int size, int nBit)
{
    int i;
	double x, ret, val, boost;
	int value;

    for (i=0;i<size;i++) {
		     
			 if (i < size/2) value = 235;
			 else value = 20; 
              
			  fputc(value,out);
			  			
	}
	file_size+=size;
}


void emit_level(int size, int nBit)
{
    int i;
	double x, ret, val, boost;
	int value;

    for (i=0;i<size;i++) {
		      x=i*360/size;
			  val = PI / 180.0;
			  value=(sin(x*val)*1.25);
              
			  boost=1;
			  if (nBit)
			     boost=1.2;
			  
			  value=(sin(x*val)* -100 );
			  fputc((value*boost)+128,out);
			  			
	}
	file_size+=size;
}


void emit_standard_square_short_level() { emit_square_level(tape_1 / 2 ,0); }
void emit_standard_square_long_level() { emit_square_level(tape_1,1);  }
void emit_standard_short_level() { emit_level(tape_1 / 2 ,0); }
void emit_standard_long_level() { emit_level(tape_1,1);  }


void emit_bit(int bit)
{
	int nBit = bit;
	if (nBit)
	{
	   if (square == 0)
		 emit_standard_long_level();
	   else
	     emit_standard_square_long_level();
	}		
		else {
			  if (square == 0)
			    emit_standard_short_level();
			  else
				emit_standard_square_short_level();
			}	 
}

void emit_byte(unsigned short n)
{
    int x;

    for(x=0;x<8;x++)
    {
        emit_bit( n & 0x80 ? 1 : 0);
        n <<= 1;
    }
    
}

void emit_pilot()
{
	int i;
	for (i=0; i<128; i++)
		emit_byte(0x00);
	
	emit_byte(0xA5);
}

int init(int argc, char *argv[])
{
	int i;
	if (argc < 3)
		return 1;
	for (i = 1; i < argc - 2; i++)
	{
		if (strcmp(argv[i], "-0") == 0) {
			tape_1 = 50*speed/22050;
			if (tape_1 %2 != 0) {
				speed = (1+(int)(tape_1 /2)) * 22050*2/50; 
				tape_1 =  (1+(int)(tape_1 /2)) * 2;
			} else speed = tape_1 /2 * 22050*2/50;  	   	   	   	   	      
		}	   	   	   	   	   	   	      	   	   
		else if (strcmp(argv[i], "-1") == 0) {
			tape_1 = 33*speed/22050;
			if (tape_1 %2 != 0) {
				speed = (1+(int)(tape_1 /2)) * 22050*2/33; 
				tape_1 =  (1+(int)(tape_1 /2)) * 2;
			} else speed = tape_1 /2 * 22050*2/33;  	   	   	       	     	 
		   
		}	   	   	   	      	   	   	       	   
		else if (strcmp(argv[i], "-2") == 0) {
			tape_1 = 25*speed/22050;			
			if (tape_1 %2 != 0) {
				speed = (1+(int)(tape_1 /2)) * 22050*2/25; 
				tape_1 =  (1+(int)(tape_1 /2)) * 2;
			} else speed = tape_1 /2 * 22050*2/25;  	   	   	     	   	   
		   
		}	   	   	   	      	   	   
		else if (strcmp(argv[i], "-3") == 0) {
			tape_1 = 20*speed/22050;			
			if (tape_1 %2 != 0) {
				speed = (1+(int)(tape_1 /2)) * 22050*2/20; 
				tape_1 =  (1+(int)(tape_1 /2)) * 2;
			} else speed = tape_1 /2 * 22050*2/20;  	   	     	     	   	   
		   
		}	   	   	   	      	   	   
		else if (strcmp(argv[i], "-4") == 0) {
			tape_1 = 16*speed/22050;			
			if (tape_1 %2 != 0) {
				speed = (1+(int)(tape_1 /2)) * 22050*2/16; 
				tape_1 =  (1+(int)(tape_1 /2)) * 2;
			} else speed = tape_1 /2 * 22050*2/16;  	   	    	     	   	   
		   
		}	   	   	   	      	   	   
		else if (strcmp(argv[i], "-5") == 0) {	  	  
			tape_1 = 14*speed/22050;			
			if (tape_1 %2 != 0) {
				speed = (1+(int)(tape_1 /2)) * 22050*2/14; 
				tape_1 =  (1+(int)(tape_1 /2)) * 2;
			} else speed = tape_1 /2 * 22050*2/14;  	   	   	     	   	   
		   
		}	 	 	 
		else if (strcmp(argv[i], "-f9") == 0) {
		   	speed = 8820;   			 	    	        	   	    
		}	    	   
		else if (strcmp(argv[i], "-f11") == 0) {
		   	speed = 11025;  			 	    	        	   	    
		}	    	       	    	
		else if (strcmp(argv[i], "-r") == 0) {
			tape_1 = 6;
			square = 1;
		   	speed = 3*3024;	    		
		}
		else if (strcmp(argv[i], "-s") == 0) {
			square = 1; 		
		}	 	    		
		else if (strcmp(argv[i], "-t") == 0) {
			tape_1 = 14*speed/22050;
			if (tape_1 %2 != 0) {
				speed = (1+(int)(tape_1 /2)) * 22050*2/14; 
				tape_1 =  (1+(int)(tape_1 /2)) * 2;
			} else speed = tape_1 /2 * 22050*2/14;	  	  	  
			square = 1;
		}	 	 
		else {
			printf("Bad option\n\n");
			return 1;
		}
	}
	sample_riff.freq = sample_riff.bytes_per_sec = speed;
	in = fopen(argv[argc - 2], "rb");
	if (in == NULL)
	{
		printf("Cannot open %s file\n\n", argv[argc - 2]);
		return 1;
	}
	out = fopen(argv[argc - 1], "wb");
	if (out == NULL)
	{
		printf("Cannot create %s file\n\n", argv[argc - 1]);
		return 1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int i, size, total_len,address;
	unsigned char len_h, len_l, load_h, load_l;
	int eot=0;
	unsigned char name,tmp_byte;

	if (init(argc, argv))
	{
		printf("Usage: %s [ -N ] <.TAP file> <.WAV file>\n", argv[0]);
		printf("Options: -f9 force speed to 8820 Hz\n");
		printf("         -f11 force speed to 11025 Hz\n");
		printf("         -0 produces a TAPE 0 WAV file\n");				  
		printf("         -1 produces a TAPE 1 WAV file\n");		
		printf("         -2 produces a TAPE 2 WAV file\n");
		printf("         -3 produces a TAPE 3 WAV file\n");
		printf("         -4 produces a TAPE 4 WAV file\n");
		printf("         -5 produces a TAPE 5 WAV file  (default is TAPE 3)\n");
		printf("         -r produces a TAPE 5 SQUARE WAV file with speed=9KHz\n");
		printf("         -s force SQUARE wave\n");		
		printf("         -t produces a TAPE 5 SQUARE WAV file\n");	  	  
		exit(1);
	}

	fwrite(&sample_riff, 1, sizeof(sample_riff), out);

	
			while (!feof(in))
			{
				
				while(!feof(in) && tmp_byte != '"')
				{
				 tmp_byte=fgetc(in);
				 if(feof(in))
				    break;	  	  	  	   
				}
                
				if(feof(in))
				    break;
				 
				emit_silence(3);
				
				
                 /* first pilot with 128 0x00 char */
				 emit_pilot();

	             emit_byte (tmp_byte);
				 printf("Program: %c",tmp_byte);
				
				tmp_byte=' ';
                while (tmp_byte!='"'){
                     tmp_byte=fgetc(in);
					 emit_byte(tmp_byte);
					 putchar(tmp_byte);
				}               
				
				/* second pilot with 128 0x00 char and 0xA5*/
				emit_pilot();
				
                char tap_type  = fgetc(in);
				printf (" Tipo: %c\n",tap_type);
				emit_byte(tap_type);

				len_h=fgetc(in);
				emit_byte(len_h);
				len_l=fgetc(in);
				emit_byte(len_l);

				
				 total_len = len_h | len_l << 8;
				 printf("Tap size: %d\n",total_len);

				if (tap_type == 'M')
				   {
					   load_h=fgetc(in);
				       emit_byte(load_h);
				       load_l=fgetc(in);
				       emit_byte(load_l);
					   address = load_h | load_l << 8;
				       printf("Address: %d\n", address);

				   }

				
				for (i=0;i<total_len;i++)
				   emit_byte(fgetc(in));
				
				
				unsigned char checksum,mistery,exec_h,exec_l;
				int entry_point;

			    if (tap_type == 'M')
					{
				       checksum=fgetc(in);
					   emit_byte (checksum);
					   printf ("Checksum: %x\n",checksum);

					   mistery=fgetc(in);
					   emit_byte(mistery);
					   printf ("Mistery Byte: %x\n",mistery);

					   
					   exec_h=fgetc(in);
					   emit_byte(exec_h);
					   exec_l=fgetc(in);
					   emit_byte(exec_l);
					   entry_point = exec_h | exec_l << 8;
				       printf("Entry point: %d\n", entry_point);
					   
					}
				
				if (tap_type == 'B')
					
					{
				       exec_h=(fgetc(in));
					   emit_byte (exec_h);
					   exec_l=(fgetc(in));
					   emit_byte (exec_l);
					   entry_point = exec_h | exec_l << 8;
				       printf("Exec Address: %d\n", entry_point);
					}

                 tmp_byte=(fgetc(in));
				 if (tmp_byte==0)
				   printf("Found end Block.\n");   
				

				/* Done block*/
				
			}
	
	printf("End Tape.\n");
	
	fclose(in);

	sample_riff.datalength = file_size;
	sample_riff.riff_size = sample_riff.datalength + 8 + sample_riff.fmtsize + 12;
	fseek(out, 0, SEEK_SET);
	fwrite(&sample_riff, 1, sizeof(sample_riff), out);

	fclose(out);
}

