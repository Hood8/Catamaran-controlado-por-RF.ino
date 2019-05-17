# Catamaran-controlado-por-RF
Código trasmisor y emisor para barco con dos motores eléctricos controlados por radiofrecuencia con dos módulos RF CC1101.

Este proyecto esta protegido por la licencia de software libre con copyleft "GNU General Public License (GPL) 3.0" y ha sido desarrollado parcialmente por principiantes por lo que no se ofrece garantía alguna y su uso queda bajo la responsabilidad 
única de sus usuarios.

 Circuito:
 
  2 Arduinos Uno u otras placas base compatibles
  2 Logic Level Converter Bi-Directional Board Module 5V/3.3V DC
  2 motores eléctricos de máximo 2 A de potencia
    
  Lista de componentes conectados a entradas:
     1 Joystick, 1 potenciómetro deslizante, 1 transceptor RF C1101
    
  Lista de componentes conectados a salidas:
     1 transceptor RF C1101, 1 Driver Board L298N (para dos motores max 2A )
     
    
    
 Desarrollo del proyecto:
 
  La idea sería seguir desarrollando el proyecto para equipar al catamarán con cámara sumergida y alimentación de los motores
  y circuitos del catamarán  mediante un panel solar que ayude a cargar las baterías al menos con el propósito de aumentar el 
  tiempo de autonomía de los dos motores (futuras mejoras y nuevas ideas para complementar al proyecto son bienvenidas).
  
  Las baterías LiPo, aunque más eficientes, cuentan con el problema de la dificultad de su carga por la necesidad de 
  balancear la carga eléctrica entre sus  células y evitar un posible incendio a bordo ya que este tipo de baterías 
  pueden inflamarse si no se cargan debidamente.Esto significa que a bordo debería de instalarse un cargador de baterias LiPo
  diseñado para evitar el sobrecalentamiento y los consiguientes daños irreversibles en estas baterías. El problema de instalar
  el cargador sería su peso, pues los que he visto en el mercado hasta ahora son de unos 500 g.
  
  Otra opción aunque mas rudimentaria sería cargar directamente una batería de 12 V de otro tipo con un panel solar de 18 V 
  con amperaje máximo de carga no muy elevado (se tiene en cuenta que la batería solo se cargaría en zonas exteriores y mientras 
  los motores estan consumiendo energía).
  
  Respecto a la cámara de vídeo, por el momento no he encontrado en el mercado alguna que se adpate a este humilde proyecto,
  que ha de ser regido por una buena relación calidad precio en concordancia con el resto de los componentes del circuito.
  
      
  

  FECHA:  26/10/2018
  AUTOR: José María Mejuto
  
