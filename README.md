# 🥢 Philosophers Simulation

Una simulación multihilo del clásico problema de los *filósofos comensales*, desarrollada en **C** usando **POSIX Threads**.  
Este proyecto pone a prueba tu conocimiento sobre **sincronización**, **condiciones de carrera** y **manejo de concurrencia** en sistemas de bajo nivel.

---

## 📚 Índice

- [📖 ¿De qué trata?](#-de-qu%C3%A9-trata)
- [🚀 Funcionalidades Destacadas](#-funcionalidades-destacadas)
- [🛠️ ¿Cómo ejecutarlo?](#%EF%B8%8F-c%C3%B3mo-ejecutarlo)
- [⚙️ Parámetros](#%EF%B8%8F-par%C3%A1metros)
- [📋 Ejemplo de Uso](#-ejemplo-de-uso)
- [✅ Pruebas Realizadas](#-pruebas-realizadas)
- [🔧 Mejoras Implementadas](#-mejoras-implementadas)
- [⚠️ Consideraciones](#%EF%B8%8F-consideraciones)
- [🌟 Posibles Mejoras Futuras](#-posibles-mejoras-futuras)
- [🤝 Contribuciones](#-contribuciones)

---

## 📖 ¿De qué trata?

El problema de los filósofos comensales es un desafío clásico de concurrencia:

> Un grupo de filósofos alterna entre **pensar**, **comer** y **dormir**.  
> Cada uno necesita **dos tenedores** (compartidos con sus vecinos) para comer.  

El objetivo es garantizar que:

- ❌ No haya **condiciones de carrera**
- 🛑 Se eviten **deadlocks**
- 🍽️ Todos los filósofos puedan comer sin morir

---

## 🚀 Funcionalidades Destacadas

- 🔒 **Sincronización de Hilos**: Mutexes para asegurar el acceso exclusivo a los tenedores  
- 🛡️ **Anti-Deadlock**: Alternancia en la toma de tenedores según el índice del filósofo  
- ⚙️ **Parámetros Dinámicos**: Configura cantidad de filósofos, tiempos y número de comidas  
- 📊 **Hilo Monitor**: Supervisa en tiempo real si algún filósofo muere  
- ⏱️ **Precisión Temporal**: Funciones optimizadas para medición exacta de tiempo

---

## 🛠️ ¿Cómo ejecutarlo?

### 🔧 Requisitos

- 🐧 Sistema operativo Linux  
- 🧰 Compilador GCC  
- 🧵 Biblioteca POSIX Threads (`pthreads`)

### 📦 Pasos

```bash
# 1. Clona el repositorio
git clone https://github.com/tu-usuario/philosophers-simulation.git
cd philosophers-simulation

# 2. Compila el proyecto
make

# 3. Ejecuta la simulación
./philo <número_de_filósofos> <time_to_die> <time_to_eat> <time_to_sleep> [número_de_comidas]
```
## ⚙️ Parámetros
<número_de_filósofos>	Número de filósofos en la simulación

<time_to_die>	Tiempo máximo (ms) sin comer antes de morir

<time_to_eat>	Tiempo que tarda en comer (ms)

<time_to_sleep>	Tiempo que tarda en dormir (ms)

[número_de_comidas]	(Opcional) Número de veces que cada filósofo debe comer antes de finalizar

## 📋 Ejemplo de Uso
```bash
./philo 5 800 200 200 5
```
Simula 5 filósofos que:

Mueren si pasan más de 800 ms sin comer

Comen durante 200 ms

Duermen durante 200 ms

Terminan cuando cada uno haya comido 5 veces

## ✅ Pruebas Realizadas
### 🔍 Pruebas Básicas
✔️ Configuración estándar: todos los filósofos completan sus comidas sin morir

✔️ Ajustes finos: solucionado un retraso en ft_print que causaba muertes prematuras

### 🧪 Pruebas de Límite
⏱️ Tiempos muy ajustados: se ajustó time_to_die para evitar muertes por acumulación de retrasos

👥 Alto número de filósofos: la simulación se mantiene estable y escalable

## 🔧 Mejoras Implementadas
🔁 Toma de tenedores alternada: evita deadlocks desde el inicio

🧠 Delay inicial (alternate_start_delay): reduce contención temprana

🕒 Precisión temporal con get_current_time

🖨️ Optimización de ft_print:

🛠️ Manejo de errores:

Protección de variables compartidas

## ⚠️ Consideraciones
⏰ Si los tiempos son muy ajustados (time_to_die ≈ time_to_eat + time_to_sleep), es probable que mueran filósofos por retrasos acumulativos

🖨️ printf puede ser costoso: evitá usarlo en simulaciones con márgenes estrechos

🔁 Escalabilidad: a mayor número de filósofos, ajustá time_to_die en consecuencia

## 🌟 Posibles Mejoras Futuras
🎨 Interfaz gráfica para ver el estado de los filósofos en tiempo real

🔄 Parámetros dinámicos que puedan cambiar durante la ejecución

⚡ Estructuras optimizadas para mayor rendimiento

## 🤝 Contribuciones
¡Las contribuciones son bienvenidas!
Encontraste un bug o tenés una idea para mejorar este proyecto, abrí un issue o mandá un PR 🙌
