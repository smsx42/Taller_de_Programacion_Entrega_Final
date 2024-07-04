Vagrant.configure("2") do |config|
  # Especifica la imagen base
  config.vm.box = "ubuntu/focal64"

  # Configura las opciones del proveedor VirtualBox
  config.vm.provider "virtualbox" do |vb|
    # Asigna 4 CPUs
    vb.customize ["modifyvm", :id, "--cpus", 4]
    # Asigna 4GB de memoria RAM
    vb.customize ["modifyvm", :id, "--memory", 4096]
    # Opcional: Aumenta la memoria de video si planeas usar resoluciones más altas
    vb.customize ["modifyvm", :id, "--vram", 256]

    vb.gui = true
  end

  # Script de aprovisionamiento para instalar el entorno de escritorio y herramientas adicionales
  config.vm.provision "shell", inline: <<-SHELL
    # Actualiza e instala el sistema operativo
    sudo apt-get update && sudo apt-get upgrade -y

    # Instala un entorno de escritorio mínimo (puedes cambiar 'ubuntu-desktop' por tu preferido)
    sudo apt-get install -y --no-install-recommends ubuntu-desktop

    # Opcional: Instala las Guest Additions de VirtualBox para una mejor integración
    sudo apt-get install -y virtualbox-guest-dkms virtualbox-guest-x11

    # Instala PulseAudio y pavucontrol para gestionar el audio
    sudo apt-get install -y pulseaudio pavucontrol

    # Instala las herramientas de compilación y dependencias necesarias
    sudo apt-get install -y build-essential git cmake

    # Instala las bibliotecas SDL2 y otras dependencias de audio
    sudo apt-get install -y libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev \
                            libasound2-dev libpulse-dev libyaml-cpp-dev

    # Clona y compila SDL desde el repositorio oficial
    git clone https://github.com/libsdl-org/SDL.git -b SDL2 /home/vagrant/SDL
    cd /home/vagrant/SDL
    mkdir build
    cd build
    cmake ..
    make
    sudo make install

    # Instala gtest para pruebas unitarias
    sudo apt-get install -y libgtest-dev
    cd /usr/src/gtest
    sudo cmake .
    sudo make
    sudo cp *.a /usr/lib

    # Instala Qt5 y sus herramientas de desarrollo
    sudo apt-get install -y qt5-default qtbase5-dev qtdeclarative5-dev

    # Crea una carpeta en el escritorio y clona el repositorio en la rama específica
    DESKTOP_DIR="/home/vagrant/Desktop/TpFinalTaller"
    mkdir -p $DESKTOP_DIR
    cp -r /vagrant/* $DESKTOP_DIR
 
    sudo chmod 777 -R $DESKTOP_DIR

    echo "Repositorio clonado en el escritorio"

    sudo reboot
  SHELL

  # Habilita la carpeta sincronizada
  config.vm.synced_folder ".", "/vagrant", disabled: false
end