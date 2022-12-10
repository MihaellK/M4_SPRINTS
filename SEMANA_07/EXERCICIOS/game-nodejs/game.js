//count para trocar imagem
count = 0;

imgP1 = document.querySelector("#imgPlayer1");
imgP2 = document.querySelector("#imgPlayer2");
divResult = document.querySelector("#result");
//link para as 3 imagens
imgOpt1 = ["https://www.pngitem.com/pimgs/m/109-1094400_rock-paper-scissors-png-clipart-rock-paper-scissor.png",
"https://www.pngitem.com/pimgs/m/266-2667252_transparent-rock-paper-scissors-clipart-rock-paper-scissors.png",
"https://www.seekpng.com/png/detail/111-1114370_rock-paper-scissors-rock-paper-scissors-clipart.png"
];
imgOpt2 = ["https://www.seekpng.com/png/detail/111-1114370_rock-paper-scissors-rock-paper-scissors-clipart.png",
"https://www.pngitem.com/pimgs/m/109-1094400_rock-paper-scissors-png-clipart-rock-paper-scissor.png",
"https://www.pngitem.com/pimgs/m/266-2667252_transparent-rock-paper-scissors-clipart-rock-paper-scissors.png"

];

//Timeout para troca de imagens

// setInterval(() => {
//     for(i=0;i<3;i++){
//         imgP1.setAttribute("src", imgOpt1[count]);
//         imgP2.setAttribute("src", imgOpt2[count]);
//     }

//     count++;

//     if (count >= 3){
//         count = 0;
//     }

//     console.log(count);
// }, 180);



function win(){
    result = JSON.stringify('{"win":"Vencey"}')
    divResult.append(result);
    console.log(result);
}

// win();