import {useState} from 'react';
import Heading from '@theme/Heading';
import styles from './styles.module.css';

const imgLogoRootPath = '/img/os-logos';

const osList = [
  'debian',
  'ubuntu',
  'fedora',
  'arch',
  'gentoo',
  'freebsd',
  'openbsd',
  'macos'
];

const logoList = [...osList, ...osList];

function Logo({name}) {
  const [imgPath, s_imgPath] = useState(`${imgLogoRootPath}/logo-bw-${name}.png`);
  const handleMouseEnter = () => {
    s_imgPath(`${imgLogoRootPath}/logo-color-${name}.png`);
  };
  const handleMouseLeave = () => {
    s_imgPath(`${imgLogoRootPath}/logo-bw-${name}.png`);
  };
  return (
    <li className={styles.logo_list_item}>
      <img onMouseEnter={handleMouseEnter} onMouseLeave={handleMouseLeave} src={imgPath} alt={name} />
    </li>
  );
}

function LogoList() {
  return (
    <ul className={styles.logo_list}>
      {logoList.map((name, idx) => (
        <Logo key={idx} name={name} />
      ))}
    </ul>
  );
}

function Carousel() {
  return (
    <div className={styles.carousel}>
      <LogoList />
    </div>
  );
}

export default function HomepageCarousel() {
  return (
    <section className={styles.container}>
      <Heading className={styles.title} as='h2'>
        Officially supported and tested on multiple OSes.
      </Heading>
      <Carousel />
    </section>
  );
}
