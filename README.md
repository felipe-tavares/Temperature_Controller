# Controlador de temperatura com controlador proporcional

+ ## Descrição geral do sistema:

  + O sistema de controle de temperatura com controlador proporcional é capaz de resfriar e aquecer o ambiente baseado na temperatura 
atual e na temperatura programada. O controlador é do tipo Proporcional e as saídas para o drive do tipo PWM. Um led de vida do sistema
(Heart Beat), oscila em 0,5Hz sempre que o sistema estiver energizado e o drive estiver habilitado. Caso driver seja desabilitado o Led
permanece aceso.

    + #### Diagrama de blocos do sistema:

<p align="center">
  <img width="500" height="320" src="diagrama_de_blocos.PNG">
</p>

+ ## Interface

  + O bloco de interface contém um display LCD 16x2 e 4 botões. O display apresenta a temperatura atual, a temperatura desejada (set-point) e o estado atual
da saída (aquecendo, resfriando, desabilitado). Os botões são utilizados para alterar os
parâmetros do controlador e o valor de set point.

      + Os botões do teclado servem para ajustar:
        + Um novo set-point.
        + Valor do ganho proporcional do controlador.
        + Desabilitar o controlador (desligar o driver independente do ajuste de
        temperatura)
        + Ligar/Desligar manualmente o aquecedor.
        + Ajustar o valor da saída do aquecedor no modo manual (0...100%).
        + Ligar/Desligar manualmente o ventilador.
        + Ajustar o valor da saída do ventilador no modo manual (0...100%).

<p align="center">
  <img width="600" height="320" src="teclado.PNG">
</p>


+ ## Funcionamento

  + O sistema se inicializa na tela de supervisório. Nela é possível observar o estado atual do controlador, os valores mínimo e máximo de histerese, o valor atual da temperatura e o setpoint configurado. Ao clicar e segurar o botão P, o sistema entra no modo de configuração. Nesse modo é possível percorrer 3 telas, sendo elas a configuração da porcentagem de histerese, o estado atual da saída para o driver e o setpoint desejado. Para alternar entre as telas, os botões LEFT e RIGHT são utilizados. Para editar alguma configuração de alguma tela, dar um clique simples no botão P e o valor pode ser alterado através das teclas laterais. Para salvar a configuração, clicar no botão P novamente. Para sair do modo de configuração e retornar para a tela supervisória, clicar e segurar novamente no botão P.
## Running the tests

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Billie Thompson** - *Initial work* - [PurpleBooth](https://github.com/PurpleBooth)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone whose code was used
* Inspiration
* etc
