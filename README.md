# 🤖 Braço Robótico de Coleta de Amostras — Docking & Retrieval

> Projeto Maker Lab — Robótica Espacial para Ambientes de Microgravidade

---

## 👥 Integrantes

| Nome completo | RM |
|---|---|
| *(Debora da Silva Amaral)* | *(550412)* |
| *(Eduardo Pielich Sanchez)* | *(99767)* |
| *(Gabriel Machado Carrara Pimentel)* | *(99880)* |
| *(Livia Namba Seraphim)* | *(97819)* |
| *(Vitor Hugo Gonçalves Rodrigues)* | *(97758)* |

---

## 🔗 Links

| Recurso | Link |
|---|---|
| 🔌 Simulador (Wokwi) | **[Abrir projeto no Wokwi](https://wokwi.com/projects/466018976755786753)** ← *substituir pelo link público* |
| 📁 Repositório GitHub | *(link deste repo)* |

---

## 📖 Descrição do Projeto

Este projeto simula um **braço robótico de captura de amostras** para operação em microgravidade, inspirado em sistemas de docking espacial. O braço possui duas articulações controladas por servomotores e é operado via comandos de texto no Monitor Serial do Arduino.

O controle permite posicionar o braço (cima/baixo) e acionar a garra (abrir/fechar) para simular a captura de uma amostra flutuante.

---

## 🧰 Componentes e Especificações Técnicas

### Pinagem do Arduino Uno

| Componente | Pino Arduino | Observação |
|---|---|---|
| Servo 1 — Braço (ombro) | **Pino 9** (PWM) | Controle de subida/descida |
| Servo 2 — Garra | **Pino 10** (PWM) | Controle de abertura/fechamento |
| LED de Status | **Pino 13** | Com resistor de 220Ω em série |
| GND | GND | Comum a todos os componentes |
| VCC servos | **5V** (fonte de bancada) | Alimentação dos servomotores |

### Tensão da Fonte de Bancada

- **Tensão configurada: 5V**
- Os servos SG90 operam na faixa de 4.8V–6V. A fonte de bancada (ou trilho VCC do simulador) deve ser configurada para **5V** para garantia de operação estável e segurança do circuito.
- O Arduino é alimentado pelo USB (5V).

---

## 🖥️ Guia de Operação — Monitor Serial

### Como abrir o Monitor Serial

1. Abra a sketch no Arduino IDE (ou clique em **Start Simulation** no Wokwi)
2. Clique no ícone 🔍 **Monitor Serial** (canto superior direito no Arduino IDE, ou no painel inferior do Wokwi)
3. Configure o baud rate para **9600**
4. Na caixa de texto, digite um dos comandos abaixo e pressione **Enter**

### Tabela de Comandos

| Comando | Ação | Servo afetado | Ângulo resultante |
|---|---|---|---|
| `U` | **Up** — Sobe o braço | Servo 1 (Braço) | 150° |
| `D` | **Down** — Desce o braço | Servo 1 (Braço) | 30° |
| `O` | **Open** — Abre a garra | Servo 2 (Garra) | 120° |
| `C` | **Close** — Fecha a garra (captura) | Servo 2 (Garra) | 10° |
| `H` | **Home** — Posição inicial | Ambos os servos | 90° / 90° |
| `S` | **Status** — Exibe ângulos atuais | — | (leitura) |

> ⚠️ Comandos aceitam letras maiúsculas ou minúsculas. Espaços e quebras de linha são ignorados.

### Sequência de captura de amostra (exemplo)

```
H   → Posição inicial
U   → Sobe o braço até a amostra
O   → Abre a garra
C   → Fecha a garra (captura)
D   → Desce o braço com a amostra
S   → Verifica ângulos finais
```

### LED de Status

| Situação | Comportamento do LED |
|---|---|
| Sistema iniciado / Home | 3 piscadas rápidas |
| Comando recebido | 1 piscada rápida |

---

## 📐 Modelagem 3D

### Software utilizado

**OpenSCAD** — modelagem paramétrica por código (arquivo `.scad`)

### Arquivo

| Arquivo | Descrição |
|---|---|
| `model/garra_braco_robotico.scad` | Projeto nativo OpenSCAD (editável) |

### Peças modeladas

1. **Base da garra** — suporte estrutural com slot para servo SG90 (9g)
2. **Dedo esquerdo / Direito** — dedos articulados com gancho de captura
3. **Elo do braço (link)** — segmento de articulação entre servos

## 🗂️ Estrutura do Repositório

```
braço-robotico-docking/
│
├── src/
│   └── braco_robotico.ino        # Código-fonte Arduino
│
├── model/
│   ├── garra_braco_robotico.scad # Projeto nativo OpenSCAD
│   └── garra_braco_robotico.stl  # Malha STL para impressão
│
├── images/
│   ├── circuito_simulador.png    # Print do circuito no Wokwi
│   └── modelo_3d_render.png      # Render da garra modelada
│
└── README.md                     # Este documento
```

---

## 🛠️ Como compilar e carregar o firmware

1. Instale o [Arduino IDE](https://www.arduino.cc/en/software) (versão 1.8+ ou 2.x)
2. A biblioteca **Servo.h** já está incluída na IDE padrão — nenhuma instalação extra é necessária
3. Abra `src/braco_robotico.ino`
4. Selecione a placa: **Arduino Uno**
5. Selecione a porta COM correspondente
6. Clique em **Upload** (→)
7. Abra o Monitor Serial em **9600 baud**

---

## 🚀 Contexto do Projeto — Microgravidade

Em ambientes de microgravidade, braços robóticos são essenciais para operações de docking, coleta de amostras e manutenção de satélites — como o braço Canadarm2 na ISS. Este projeto simula essa funcionalidade em escala didática, com foco em:

- **Precisão de posicionamento** (movimento suave, grau a grau)
- **Feedback visual** (LED de status)
- **Garra com gancho** projetada para prender objetos sem gravidade auxiliar

---

*Projeto desenvolvido para a disciplina Project-Based Maker Lab*