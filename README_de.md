<p align="center">
<img src="documentation/figures/logo.png" width="60%" >
</p>

 [English](README.md) | [中文](README_zh.md) | [Español](README_es.md) | **Deutsch**

[![GitHubStars](https://img.shields.io/github/stars/RT-Thread/rt-thread?style=flat-square&logo=GitHub)](https://github.com/RT-Thread/rt-thread/stargazers)
[![GiteeStars](https://gitee.com/rtthread/rt-thread/badge/star.svg?theme=gvp)](https://gitee.com/rtthread/rt-thread/stargazers)
[![GitHub](https://img.shields.io/github/license/RT-Thread/rt-thread.svg)](https://github.com/RT-Thread/rt-thread/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RT-Thread/rt-thread.svg)](https://github.com/RT-Thread/rt-thread/releases)
[![Gitter](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/RT-Thread/rt-thread?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
[![GitHub pull-requests](https://img.shields.io/github/issues-pr/RT-Thread/rt-thread.svg)](https://github.com/RT-Thread/rt-thread/pulls)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat)](https://github.com/RT-Thread/rt-thread/pulls)

# RT-Thread

RT-Thread wurde 2006 geboren und ist ein quelloffenes, neutrales und gemeinschaftsbasiertes Echtzeitbetriebssystem (RTOS).

RT-Thread ist hauptsächlich in der Sprache C geschrieben, leicht zu verstehen und einfach zu portieren (kann schnell auf eine breite Palette von Mainstream-MCUs und Modul-Chips portiert werden). Es wendet objektorientierte Programmiermethoden auf das Design von Echtzeitsystemen an, wodurch der Code elegant, strukturiert, modular und sehr anpassbar ist.

RT-Thread gibt es in einer Standard- und einer Nano-Version. Für ressourcenbeschränkte Mikrocontroller (MCU)-Systeme kann die Nano-Version, die nur 3KB Flash- und 1,2KB RAM-Speicherressourcen benötigt, mit einfach zu bedienenden Tools angepasst werden. Für ressourcenreiche IoT-Geräte kann RT-Thread das Online-Tool zur Verwaltung von Softwarepaketen zusammen mit Systemkonfigurationswerkzeugen verwenden, um einen intuitiven und schnellen modularen Zuschnitt zu erreichen und umfangreiche Softwarepakete nahtlos zu importieren.

RT-Thread-Architektur

RT-Thread verfügt nicht nur über einen Echtzeit-Kernel, sondern auch über umfangreiche Komponenten. Seine Architektur ist wie folgt:


![architecture](./documentation/figures/architecture.png)


Sie umfasst:

- Kernel-Schicht: RT-Thread-Kernel, das Kernstück von RT-Thread, umfasst die Implementierung von Objekten im Kernel-System, wie z. B. Multi-Threading und dessen Scheduling, Semaphor, Mailbox, Nachrichtenwarteschlange, Speicherverwaltung, Timer usw.; libcpu/BSP (Chip Migration Related Files/Board Support Package) ist eng mit der Hardware verbunden und besteht aus Peripherie-Treibern und CPU-Portierung.

- Komponenten und Dienstebene: Die Komponenten basieren auf Software der oberen Ebene des RT-Thread-Kernels, wie z. B. virtuelle Dateisysteme, FinSH-Befehlszeilenschnittstellen, Netzwerk-Frameworks, Geräte-Frameworks und mehr. Der modulare Aufbau ermöglicht eine hohe interne Kohäsion innerhalb der Komponenten und eine geringe Kopplung zwischen den Komponenten.

- [RT-Thread-Softwarepaket](https://packages.rt-thread.org/en/index.html): Eine Allzweck-Softwarekomponente, die auf der IoT-Betriebssystemplattform RT-Thread für verschiedene Anwendungsbereiche läuft und aus Beschreibungsinformationen, Quellcode oder Bibliotheksdateien besteht. RT-Thread bietet eine offene Paketplattform mit offiziell verfügbaren oder von Entwicklern bereitgestellten Paketen, die Entwicklern eine Auswahl an wiederverwendbaren Paketen bieten, die ein wichtiger Teil des RT-Thread-Ökosystems sind. Das Paket-Ökosystem ist für die Wahl eines Betriebssystems von entscheidender Bedeutung, da diese Pakete in hohem Maße wiederverwendbar und modular sind, was es den Anwendungsentwicklern erleichtert, das gewünschte System in kürzester Zeit zu erstellen. RT-Thread unterstützt mehr als 370 Softwarepakete.

## RT-Thread Merkmale

- Der minimale Kernel wurde für Geräte mit begrenzten Ressourcen entwickelt und benötigt nur 1,2 KB RAM und 3 KB Flash.
- Eine Vielzahl von Standardschnittstellen, wie POSIX, CMSIS, C++ Anwendungsumgebung.
- Verfügt über zahlreiche Komponenten und ein florierendes und schnell wachsendes Paket-Ökosystem.
- Eleganter Codestil, einfach zu verwenden, zu lesen und zu beherrschen.
- Hohe Skalierbarkeit. RT-Thread hat eine hochwertige skalierbare Software-Architektur, lose Kopplung, Modularität, ist leicht anzupassen und zu erweitern.
- Unterstützt Hochleistungsanwendungen.
- Unterstützt alle gängigen Kompilierwerkzeuge wie GCC, Keil und IAR.
- Unterstützt eine breite Palette von <a href="https://www.rt-thread.io/board.html">architekturen und chips</a>.

## Code-Katalog

   Der RT-Thread-Quellcodekatalog wird wie folgt dargestellt:

| Name          | Beschreibung                                             |
| ------------- | ------------------------------------------------------- |
| BSP          | Board Support Package basierend auf der Portierung von verschiedenen Entwicklungsboards. |
| Komponenten    | Komponenten, wie Shell, Dateisystem, Protokollstapel usw. |
| Dokumentation | Verwandte Dokumente, wie Coding Style, Doxygen usw.        |
| Beispiele      | Zugehöriger Beispielcode.                                 |
| einschließen   | Kopfdateien des RT-Thread-Kernels.                        |
| libcpu        | CPU-Portierungscode wie ARM/MIPS/RISC-V usw. |
| src           | Die Quelldateien für den RT-Thread-Kernel. |
| Werkzeuge     | Die Skriptdateien für das RT-Thread Befehlserstellungswerkzeug.  |

RT-Thread wurde inzwischen für fast 200 Entwicklungsboards portiert, die meisten BSPs unterstützen MDK, IAR-Entwicklungsumgebung und GCC-Compiler und bieten ein Standard-MDK- und IAR-Projekt, das es den Benutzern ermöglicht, ihren eigenen Anwendungscode direkt auf der Grundlage des Projekts hinzuzufügen. Jedes BSP hat eine ähnliche Verzeichnisstruktur, und die meisten BSPs bieten eine README.md-Datei, eine Datei im Markdown-Format, die eine grundlegende Einführung in das BSP enthält und erklärt, wie man einfach mit dem BSP beginnt.

# Ressourcen

## Unterstützte Architekturen

RT-Thread unterstützt viele Architekturen und hat die wichtigsten Architekturen in aktuellen Anwendungen abgedeckt. Architektur und beteiligter Chip-Hersteller:

- **ARM Cortex-M0/M0+**：manufacturers like ST
- **ARM Cortex-M3**：manufacturers like ST、Winner Micro、MindMotion, ect.
- **ARM Cortex-M4**：manufacturers like ST、Infineon、Nuvoton、NXP、[Nordic](https://github.com/RT-Thread/rt-thread/tree/master/bsp/nrf5x)、GigaDevice、Realtek、Ambiq Micro, ect.
- **ARM Cortex-M7**：manufacturers like ST、NXP
- **ARM Cortex-M23**：manufacturers like GigaDevice
- **ARM Cortex-M33**：manufacturers like ST
- **ARM Cortex-R4**
- **ARM Cortex-A8/A9**：manufacturers like NXP
- **ARM7**：manufacturers like Samsung
- **ARM9**：manufacturers like Allwinner、Xilinx 、GOKE
- **ARM11**：manufacturers like Fullhan
- **MIPS32**：manufacturers like loongson、Ingenic
- **RISC-V RV32E/RV32I[F]/RV64[D]**：manufacturers like Hifive、[Kendryte](https://github.com/RT-Thread/rt-thread/tree/master/bsp/k210)、[bouffalo_lab](https://github.com/RT-Thread/rt-thread/tree/master/bsp/bouffalo_lab)、[Nuclei](https://nucleisys.com/)、[T-Head](https://www.t-head.cn/)
- **ARC**：manufacturers like SYNOPSYS
- **DSP**：manufacturers like TI
- **C-Sky**
- **x86**

## Unterstützte IDE und Compiler

Die wichtigsten von RT-Thread unterstützten IDEs/Compiler sind:

- RT-Thread Studio IDE
- MDK KEIL
- IAR
- GCC

## RT-Thread Studio IDE

[User Manual](https://www.rt-thread.io/document/site/rtthread-studio/um/studio-user-manual/) | [Tutorial Videos](https://youtu.be/ucq5eJgZIQg)

RT-Thread Studio IDE (auch bekannt als RT-Studio) ist eine integrierte Entwicklungsumgebung aus einer Hand, die vom RT-Thread-Team entwickelt wurde. Es verfügt über ein einfach zu bedienendes grafisches Konfigurationssystem und eine Fülle von Software-Paketen und Komponenten Ressourcen. RT-Studio verfügt über Funktionen zur Projekterstellung, -konfiguration und -verwaltung sowie zur Code-Bearbeitung, SDK-Verwaltung, Build-Konfiguration, Debugging-Konfiguration, Programm-Download und Debugging. Wir sind bestrebt, die Nutzung von RT-Studio so intuitiv wie möglich zu gestalten, Doppelarbeit zu reduzieren und die Effizienz der Entwicklung zu verbessern.

![studio](./documentation/figures/studio.gif)

## Env-Werkzeug

[User Manual](documentation/env/env/) | [Tutorial Videos](https://www.youtube.com/watch?v=dEK94o_YoSo)

In der Anfangsphase schuf das RT-Thread-Team auch ein Hilfswerkzeug namens Env. Dabei handelt es sich um ein Hilfstool mit einer TUI (textbasierten Benutzeroberfläche). Entwickler können das Env-Tool verwenden, um GCC, Keil MDK und IAR-Projekte zu konfigurieren und zu generieren.

![env](./documentation/figures/env.png)

# Erste Schritte

[RT-Thread Programmierhandbuch](https://www.rt-thread.io/document/site/tutorial/quick-start/introduction/introduction/) | [RT-Thread Studio IDE](https://www.rt-thread.io/studio.html) | [Kernel Sample](https://github.com/RT-Thread-packages/kernel-sample) | [RT-Thread Einsteigerhandbuch](https://www.youtube.com/watch?v=ZMi1O-Rr7yc&list=PLXUV89C_M3G5KVw2IerI-pqApdSM_IaZo)

Basierend auf [STM32F103 BluePill](https://github.com/RT-Thread/rt-thread/tree/master/bsp/stm32/stm32f103-blue-pill) | [Raspberry Pi Pico](https://github.com/RT-Thread/rt-thread/tree/master/bsp/raspberry-pico)

## Simulator

Das RT-Thread BSP kann direkt kompiliert und zur Verwendung auf das entsprechende Entwicklungsboard heruntergeladen werden. Darüber hinaus bietet RT-Thread auch das qemu-vexpress-a9 BSP, das ohne Hardware-Plattform verwendet werden kann. Weitere Informationen finden Sie in der Anleitung für die ersten Schritte unten.
[Windows](documentation/quick-start/quick_start_qemu/quick_start_qemu.md) | [Linux Ubuntu](documentation/quick-start/quick_start_qemu/quick_start_qemu_linux.md) | [Mac OS](documentation/quick-start/quick_start_qemu/quick_start_qemu_macos.md)

# Lizenz

RT-Thread ist eine Open-Source-Software und steht seit v3.1.1 unter der Apache License Version 2.0. Lizenzinformationen und Copyright-Informationen sind in der Regel am Anfang des Codes zu finden:

```c
/* Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 * ...
 */
```

# Gemeinschaft

RT-Thread ist sehr dankbar für die Unterstützung durch alle Entwickler der Community. Wenn Sie Ideen, Vorschläge oder Fragen zur Verwendung von RT-Thread haben, können Sie RT-Thread über die folgenden Kanäle erreichen, und wir aktualisieren RT-Thread auch in Echtzeit über diese Kanäle. Gleichzeitig können alle Fragen im [Issue-Bereich des RT-Thread-Repositorys](https://github.com/RT-Thread/rt-thread/issues) oder im [RT-Thread-Forum](https://club.rt-thread.io/),  gestellt werden, und die Community-Mitglieder werden sie beantworten.

[Website](https://www.rt-thread.io) | [Github](https://github.com/RT-Thread/rt-thread) | [Twitter](https://twitter.com/rt_thread) | [LinkedIn](https://www.linkedin.com/company/rt-thread-iot-os/posts/?feedView=all) | [Youtube](https://www.youtube.com/channel/UCdDHtIfSYPq4002r27ffqPw) | [Facebook](https://www.facebook.com/RT-Thread-IoT-OS-110395723808463/?modal=admin_todo_tour) | [Medium](https://rt-thread.medium.com/)

# Beitrag

Wenn Sie an RT-Thread interessiert sind und sich an der Entwicklung von RT-Thread beteiligen und einen Beitrag zum Code leisten wollen, lesen Sie bitte den [Code Contribution Guide](documentation/contribution_guide/contribution_guide.md).

