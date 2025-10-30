# 🛰️ IoT Challenge

### 👥 Integrantes
| Nome | RM |
|------|----|
| **Pedro Manzo Yokoo** | 556115 |
| **Fernando Fernandes Prado** | 557982 |
| **Guilherme Camasmie Laiber de Jesus** | 554894 |

---

## ⚙️ Como Montar o IoT

<p align="center">
  <img width="779" height="671" alt="Montagem do IoT" src="https://github.com/user-attachments/assets/0fa9849e-7f23-4e1c-a041-0a8c3ebf2045" />
</p>

<p align="center">
  <img src="https://github.com/user-attachments/assets/ba3e63e0-8132-4992-b529-07a9696fbbbf" width="400">
  <img src="https://github.com/user-attachments/assets/1681b516-4f09-47b7-8e7e-b16d29146f59" width="400">
</p>

---

## 💻 Como Usar o Código

### 🔹 1. Configuração no **Arduino IDE**

1. Abra a **IDE do Arduino**.
2. Vá em **File → Open** e selecione o arquivo `.ino` do projeto.
   
   ![Abrindo o arquivo](https://github.com/user-attachments/assets/7d4895f4-ee8a-44d5-9289-3b2daae4fec5)

3. Selecione a **placa correta**:
   - Vá em **Tools → Board → ESP32 Arduino → ESP32 Dev Module**.

   <img width="284" height="32" alt="Selecionando ESP32" src="https://github.com/user-attachments/assets/a9c708e6-700a-4085-807a-7529f3c25dd0" />

4. Clique em **Upload** para enviar o código para o dispositivo.

   ![Upload do código](https://github.com/user-attachments/assets/f95c256b-a223-40c8-9644-536dfdfa06dc)

---

### 🔹 2. Configuração do **Google Sheets**

1. Acesse [Google Spreadsheets](https://docs.google.com/spreadsheets) e crie uma nova planilha.
2. Renomeie-a para **“Acesso RFID”**.

   ![Nova planilha](https://github.com/user-attachments/assets/9c7f663b-ddf4-4f78-89a3-262c536f5648)

3. Vá em **Extensões → App Script**.

   <img width="397" height="266" alt="Acessando o App Script" src="https://github.com/user-attachments/assets/d299d3e3-325e-4a97-83f2-f953f532e511" />

4. Cole o **código do arquivo .txt** fornecido no editor do App Script.

5. Clique em **Nova Implementação** e configure:
   - **Quem pode acessar** → `Qualquer pessoa`.

   ![Configuração da implementação](https://github.com/user-attachments/assets/16f6980c-4850-4aa1-b2b5-dc0f18b98c2c)

---

## 📊 Visualizando os Dados

Para exibir um **gráfico na planilha**:
1. Selecione todas as colunas da tabela.
2. Vá em **Inserir → Gráfico**.
3. Escolha o tipo de gráfico que melhor representa os dados coletados.

---

## ✅ Pronto!

Seu projeto IoT está configurado e funcional!  
A partir daqui, você poderá:
- Registrar leituras do **RFID** diretamente na planilha;
- Analisar os dados visualmente através dos gráficos;
- Monitorar o comportamento do sistema em tempo real.

---

<p align="center">🚀 Desenvolvido com dedicação para o <b>Challenge IoT</b> da FIAP</p>
