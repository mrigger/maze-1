#include <stdio.h>
#include <stdlib.h>
#define Maxm 30
#define Maxn 30

struct m{  // �������򣬰��Ӷ���˳ʱ�뷽��
	int dx; // ��������
	int dy;	// ��������
} move[8] = { {0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1} }; 

typedef struct qnod{ // ���еĽڵ�
	int x; // ��¼������������
	int y; // ��¼������ 
	int pre; //����õ�ĳ������ڶ����е��±�
}qnode;

void creatmaze(int *maze,int m,int n) // ���������0��1�������Թ���m���У�n����
{
	int row = m+2;
	int pol = n+2;
	int r,p;

	for ( r=0; r < row ; r++){
		if( r == 0 || r == row -1){ // �ڵ�һ�к����һ�и����һ��ǽ(Ϊ1)
			for ( p = 0 ; p < pol ; p++ )
				maze[r*Maxm+p] = 1;
		}
		else {
			for ( p = 0 ; p < pol; p++){
				if ( p == 0 || p == pol -1) //�ڵ�һ�к����һ�� ���һ��ǽ
					maze[r*Maxm+p] = 1;
				else if ( r == 1 && p == 1 || r == row -2 && p == pol - 2) // (1,1)Ϊ��ڣ�(m,n)Ϊ���ڣ�����Ϊ0
					maze[r*Maxm+p] = 0;
				else { // ������λ�ò��������0��1
					maze[r*Maxm+p] =rand()% 2 ;
				}
			}// for
		}// else
	} // for
}		

int findminpath( int *maze,qnode queue[],int m , int n)
{

	int front = 0; int rear = 0; // frontָ��ʵ�ʵĶ��ף�rearָ���β
	
	int i,j,i1,j1; // �����(i,j)

	int dir; // ����

	queue[0].x = 1; // ���г�ʼ����Ϊ��ڵ�
	queue[0].y = 1;
	queue[0].pre = -1;
	maze [Maxm + 1] = -1;

	while( !(queue[front].x ==m && queue[front].y == n)) {// ���ǳ��ڵ�
		i = queue[front].x;
		j = queue[front].y;

		for(dir = 0; dir < 8; dir++){ // ���ڽ�ͨ���Ž�ջ
			i1 = i+move[dir].dx;
			j1 = j+move[dir].dy;			
			if( maze [i1 * Maxm + j1] == 0 ){
				rear++;         
				queue[rear].x = i1;
				queue[rear].y = j1;
				queue[rear].pre = front;
				maze [i1 * Maxm + j1] = -1; // �����߹���λ�ý�0��Ϊ-1
			}
		}
		if(front == rear){ // ջ�� , ʧ��
			printf("\nTHERE IS NO PATH.\n");
			return 0;
		}
		else { // frontָ����е���һ��Ԫ��
			front ++;
		}
		
	}// while

	while(queue[front].pre != -1){
		printf("(%d , %d) --> ",queue[front].x,queue[front].y);
		front = queue[front].pre;
	}
	printf("(1 , 1)");

	return 1;
}

int main()
{
	int m,n;
	int i,j;
	char repeatflag;
	int maze[Maxm][Maxn];
	qnode queue[Maxm * Maxn];// ���ڱ����ѵ���������
	do{
		printf("�����Թ��������볤�� n = ");
		scanf("%d",&n);
		printf("������߶� m = ");
		scanf("%d",&m);
		printf("\n");

		creatmaze(maze[0],m,n);

		for (i = 0 ; i< m+2; i ++){
			for (j = 0 ; j < n+2 ;j++){
				printf("%d  ",maze[i][j]);
				
			}
			printf("\n");
			
		}
		findminpath ( maze[0],queue, m , n) ;
		getchar();

		printf("\nҪ����һ����? (����'n'����������Ҫ,'y'����Ҫ)\n");
		scanf("%c",&repeatflag);
	}while(repeatflag == 'y');
}



	