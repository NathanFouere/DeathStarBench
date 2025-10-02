## Emscripten

Emscripten est un compilateur source à source open source permettant de compiler du bitcode LLVM en asm.js, qui peut être exécuté par les navigateurs web.

Le bytecode LLVM étant généré à partir de programmes écris en C ou C++, par extension Emscripten permet donc de compiler un programme C ou C++ en javascript et en WebAssembly

Emcc utilise Clang et LLVM pour être compilé en WebAssembly. Il crééer également du javascript qui fournit une API de support au code compilé en Web Assembly. Ce Javascript peut être exécuté par NodeJs ou depuis un fichier un html dans un navigateur.

### Exemple 

Pour afficher hello world en C on on aura le code suivant :

```c
// test.C
#include <stdio.h>

int main() {
markdown
    printf("Hello World \n");

    return 0;
}
```

En lançant la commande `emcc test.c ` on obtiendra deux fichiers :
1. a.out.js
2. a.out.wasm

Le premier est un fichier javascript classique, le second est en WebAssembly.

On peut le code généré avec la commande `node a.out.js`. Ce code js servira d'interface avec le code web assembly produit.

## Connexion entre code C/C++ et Js

Emscripten permet de faire communiquer du code javascript et C/C++. On peut:
* Appeler des fonctions C déjà compilé directement depuis du Js
* Appeler des classes C++ depuis javascript
* Appeler des fonctions javascript depuis du C et du C++

## Sources et documentation transmise par le professeur

- [Grosse liste d’applis portées avec Emscripten](https://github.com/emscripten-core/emscripten/wiki/Porting-Examples-and-Demos)
- The browser is the computer (présentation @ WASM IO)
    - [Vidéo](https://www.youtube.com/watch?v=T5cT3U2afC0)
    - [Slides](https://speakerdeck.com/angelmmiguel/o?slide=2)
- Emscripten
    - [Networking](https://emscripten.org/docs/porting/networking.html)
- [WasmLinux (démo)](https://wasmlinux-demo.pages.dev/)
- [Fledger — cross-platform network programming in WASM libc (EPFL C4DT)](https://c4dt.epfl.ch/article/cross-platform-network-programming-in-wasm-libc/)
- Container to WASM (utilise VM, hors scope mais culture générale)
    - [container2wasm](https://github.com/container2wasm/container2wasm)
- [Tokio with WASM (Rust)](https://github.com/cunarist/tokio-with-wasm)
- [WASM it (Rust)](https://azriel.im/wasm_it/)
- PgLite — Postgres dans le navigateur
    - [Site](https://pglite.dev/)
- WebAssembly sur architectures exotiques
    - [Note](https://anil.recoil.org/notes/wasm-on-exotic-targets)
- Postgres WASM (autre Postgres dans le navigateur)
    - [Article Supabase](https://supabase.com/blog/postgres-wasm)
- Compiler du C vers WebAssembly sans Emscripten
    - [Article](https://surma.dev/things/c-to-webassembly/)
- 


## Application Social Network

![Social Network Architecture](figures/socialNet_arch.png)


## Sources
* https://fr.wikipedia.org/wiki/Emscripten
* https://emscripten.org/docs/introducing_emscripten/about_emscripten.html
* https://fr.wikipedia.org/wiki/Apache_Thrift
* https://emscripten.org/docs/porting/connecting_cpp_and_javascript/Interacting-with-code.html