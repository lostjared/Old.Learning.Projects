
class ArrayOf : public mxObject {
    Uint32 color;
    bool explo;
    void logic();
    public:
        ArrayOf();
        void render();
        void setDirection(int x, int y, int direction);      
        void setColor(Uint32 color);
        int x_pos, y_pos,direction,color_r,color_g,color_b;
        int which;
};

ArrayOf::ArrayOf()
{
    mx = 0;
    which = 0;
}    

void ArrayOf::setDirection(int x, int y, int direction)
{
    this->direction = direction;
    this->x_pos = x;
    this->y_pos = y;    
}


void ArrayOf::render()
{
    logic();
    if(mx != 0)
    if(which == 0)
     mx->setPixel(mx->pscr,x_pos,y_pos,color_r,color_g,color_b);
     else
     mx->setPixel(mx->pscr,x_pos,y_pos,color);
     
}   

void ArrayOf::logic()
{
   switch(direction)
   {
       case 0:
           x_pos += 2;
           y_pos -= 2;
       break;
       case 1:
                x_pos++;
                y_pos++;
                break;
       case 2:
                x_pos--;
                y_pos++;
                break;
       case 3:
                  y_pos--;
                  x_pos--;
                break;
                  case 4:
              x_pos++;
              y_pos--;
       break;
       case 5:
           y_pos--;
           explo = true;
           break;
           case 6:
               y_pos++;
               explo = true;
               break;
               
                       
     }
     
     static int wait = 0;
     if(explo == true && ++wait > 25)
     {
         direction = rand()%4;
         explo = false;  
         wait = 0;
     }                
                  
     if(x_pos <= 0 || y_pos <= 0 || x_pos >= 640 || y_pos >= 480)
     {
         setDirection(rand()%640,rand()%480,rand()%4);
         explo = false;
     }
                         
}

void ArrayOf::setColor(Uint32 color)
{
    this->color = color;   
    which = 1;
}

