# Macro Deck

Firmware e Software para um Macro Deck baseado em Raspberry Pi Pico (RP2040), desenvolvido do zero em C++ utilizando Pico SDK e TinyUSB.

O objetivo é criar um dispositivo totalmente **plug and play**, reconhecido como teclado HID pelo computador, sem necessidade de software residente.

---

# Objetivos

- Firmware próprio escrito em C++
- Arquitetura orientada a objetos
- Utilização do Pico SDK
- Comunicação USB HID via TinyUSB
- Matriz de teclas
- LEDs individuais por tecla
- Encoders (knobs) rotativos para controle de volume e outras funções
- Perfis armazenados na memória Flash
- Configuração via software desktop
- Atualização de firmware via USB
- Suporte a macros
- Hardware open source

---

# Hardware

Planejamento inicial:

- Raspberry Pi Pico (RP2040)
- 10 switches mecânicos
- 10 LEDs vermelhos
- 10 diodos para matriz
- 5 encoders rotativos
- Multiplexador analógico (futuro)
- Estrutura impressa em 3D

---

# Arquitetura

```
Application
│
├── HAL
│   ├── Clock
│   ├── GPIO
│   ├── DigitalInput
│   ├── DigitalOutput
│   ├── PeriodicTimer
│   └── OneShotTimer
│
├── Devices
│   ├── Led
│   └── Button
│
├── Keyboard
│   └── KeyboardMatrix
│
└── USB
    └── (em desenvolvimento)
```

---

# Roadmap

## ✅ Marco 1 - Estrutura do Projeto

- [x] Configuração do Pico SDK
- [x] Estrutura inicial do projeto
- [x] Loop principal
- [x] LED de status

---

## ✅ Marco 2 - HAL e Entrada de Dados

### HAL

- [x] GPIO
- [x] DigitalInput
- [x] DigitalOutput
- [x] Clock
- [x] PeriodicTimer
- [x] OneShotTimer

### Devices

- [x] LED
- [x] button

### Keyboard

- [x] KeyboardMatrix
- [x] Debounce
- [x] Eventos Pressed/Released

---

## 🚧 Marco 3 — USB HID

Objetivo:

Transformar o dispositivo em um teclado USB totalmente funcional.

### Etapas

- [x] Configurar TinyUSB
- [x] Criar USB Descriptors
- [x] Inicializar USB
- [x] Enumerar como teclado HID
- [x] Enviar relatórios de pressionamento
- [x] Enviar relatórios de liberação
- [x] Integrar a matriz de teclas (KeyboardMatrix)
- [x] Suporte a múltiplas teclas com 6KRO
- [x] Criar perfil padrão independente da aplicação
- [ ] NKRO - melhoria futura

---

## ⏳ Marco 4 — Motor de Ações

- [ ] InputManager
- [ ] MacroEngine
- [ ] Atalhos
- [ ] Sequências de teclas
- [ ] Camada de abstração entre teclado e USB

---

## ⏳ Marco 5 — Perfis

- [ ] Estrutura de perfis
- [ ] Memória Flash
- [ ] Carregamento
- [ ] Alternância de perfis

---

## ⏳ Marco 6 — Knobs

- [ ] Driver de Encoder
- [ ] Controle de Volume
- [ ] Funções configuráveis

---

## ⏳ Marco 7 — Software Desktop

- [ ] Detectar dispositivo
- [ ] Configurar teclas
- [ ] Configurar knobs
- [ ] Atualizar firmware
- [ ] Gerenciar perfis

---

## ⏳ Marco 8 — Recursos Avançados

- [ ] RGB (caso futuramente substitua LEDs)
- [ ] Macros complexas
- [ ] Controle multimídia
- [ ] Múltiplas camadas
- [ ] Modo Bootloader
- [ ] Configuração via USB HID

---

# Estado Atual

Versão atual: **v0.2.0**

## Implementado

- Arquitetura do firmware
- HAL
- Timers
- GPIO
- Matriz de teclado
- Debounce
- Eventos de teclado
- LED de status

## Próximo passo

Implementar o dispositivo USB HID utilizando TinyUSB.