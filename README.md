# C-Pong
Reviva o clássico com esta recriação minimalista. Jogado inteiramente no terminal, provando que a diversão de 1972 ainda cabe em algumas linhas de C.

## Como executar

Instruções rápidas para quem clonou este repositório.

1. Clone o repositório:

```bash
git clone https://github.com/gabrielfariaxs/C-Pong.git
cd C-Pong
```

2. Compile (Linux / WSL):

```bash
# comando genérico que compila todos os fontes em src/
gcc -o pong src/*.c -I. -lm
# ou listando os arquivos explicitamente:
gcc src/function.c src/keyboard.c src/main.c -I. -lm -o pong
```

3. Execute:

```bash
./pong
```

Observações:

- Recomendamos usar WSL (Windows Subsystem for Linux) se estiver em Windows, pois o jogo usa APIs POSIX (`termios`, `usleep`).
- Se estiver compilando diretamente em `/mnt/c/...` e receber `chmod: Operation not permitted`, copie o projeto para o filesystem do WSL (por exemplo `~/c-pong`) e compile lá.
- Para rodar a partir do PowerShell sem abrir o WSL manualmente, você pode usar:

```powershell
wsl bash -lc "cd /mnt/c/Users/<seu_usuario>/C-Pong && gcc -o pong src/*.c -I. -lm && ./pong"
```

- Se quiser um executável nativo do Windows, será necessário portar o input/console (substituir `termios`) ou usar Cygwin/MinGW.

Divirta-se!
